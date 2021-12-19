#ifndef SAVEREADER_CPP_I
#define SAVEREADER_CPP_I

#include <fstream>
#include <iostream>
#include <bitset>
#include <string>
#include "List.hpp"
#include "PokemonBox.hpp"
#include "StringConverter.hpp"
#include "GameOptions.hpp"
#include "PlayTime.hpp"
#define uchar unsigned char

class SaveReader{
public:
    static const unsigned short BANK_SIZE = 0x2000;

    bool debugMode;
    char data[BANK_SIZE*4];

    // Constructor for C++ std string as filename
    SaveReader(bool dbug, std::string filename){
        debugMode = dbug;

        std::ifstream savedata(filename, std::ios::binary);
        if(!savedata){
            std::cerr << "Couldn't initialize the input file stream!" << std::endl;
            return;
        }
        else{
            savedata.read(data, BANK_SIZE*4);
        }
    }

    // Same as above for .NET Strings
    SaveReader(bool dbug, System::String^ filename) {
        debugMode = dbug;
        std::string stdFilename = PkmStringConverter::toStdString(filename);
        std::ifstream savedata(stdFilename, std::ios::binary);
        if (!savedata) {
            std::cerr << "Couldn't initialize the input file stream!" << std::endl;
            return;
        }
        else {
            savedata.read(data, BANK_SIZE * 4);
        }
    }

    // Read a string from the save file, starting at OFFSET until it finds a 0 character or it reads len characters
    std::string readString(unsigned short OFFSET, uchar len){
        std::string res = "";
        for(int i = 0; i < len && PkmStringConverter::decodeChar(data[OFFSET + i]) != '\0'; i++){
            res += data[OFFSET + i];
        }
        return res;
    }

    // Returns true if the pokemon with the given pokedex value has been seen, false if not
    // In the file, whether a pokemon was seen or not is stored in a bit array. For example, if the
    // start of the array is 11011011 01101101, to know if the pokemon with the pokedex value 12 has
    // been seen, just see if the 12th bit is 1 or 0. 1 = true, 0 = false
    bool isPokemonSeen(uchar pokedexValue){
        unsigned short OFFSET = 0x25b6;

        uchar pokeNum = pokedexValue-1;
        uchar byte = pokeNum / 8;
        uchar bit = pokeNum % 8;
        uchar byteVal = data[OFFSET + byte];
        byteVal = byteVal >> bit;
        byteVal = byteVal & 1;
        return byteVal;
    }

    // Same as above, but if the pokemon has been caught instead of seen
    bool isPokemonCaught(uchar pokedexValue){
        unsigned short OFFSET = 0x25a3;
        
        uchar pokeNum = pokedexValue-1;
        uchar byte = pokeNum / 8;
        uchar bit = pokeNum % 8;
        uchar byteVal = data[OFFSET + byte];
        byteVal = byteVal >> bit;
        byteVal = byteVal & 1;
        return byteVal;
    }

    // Retrieves a binary coded decimal (BCD) in OFFSET across SIZE bytes
    // An example of a binary coded value would be 10010111 01010101, where it is equal to 9755
    // 1001 = 9; 0111 = 7; 0101 = 5; 0101 = 5
    unsigned int getBinaryCodedValue(unsigned short OFFSET, unsigned short SIZE){
        std::string res = "";
        for(int i = 0; i < SIZE; i++){
            uchar firstHalf = data[OFFSET + i] >> 4;
            firstHalf = firstHalf & 0b00001111;
            uchar secondHalf = data[OFFSET + i] & 0b00001111;
            res += std::to_string(firstHalf) + std::to_string(secondHalf);
        }
        return stoi(res);
    }

    // Returns the trainer's money, which is stored as a BCD
    unsigned int getTrainerMoney(){
        const unsigned short OFFSET = 0x25F3;
        const unsigned short SIZE = 0x3;
        return getBinaryCodedValue(OFFSET, SIZE);
    }

    // Returns the trainer's casino coins, which is stored as a BCD.
    unsigned int getTrainerCoins(){
        const unsigned short OFFSET = 0x2850;
        const unsigned short SIZE = 0x2;
        return getBinaryCodedValue(OFFSET, SIZE);
    }

    // Returns an item list stored in OFFSET. The byte at OFFSET represents the amount of items in the list,
    // The following 2*count bytes represent the item's index and amount.
    List getList(unsigned short OFFSET){
        uchar count = data[OFFSET++];
        List res;
        res.length = count;
        res.items = (ListEntry*)malloc(count*sizeof(ListEntry));
        for(int i = 0; i < count; i++){
            res.items[i].index = data[OFFSET+(i*2)];
            res.items[i].amount = data[OFFSET+(i*2)+1];
        }
        return res;
    }

    // Returns the list of items in the player's backpack
    List getBackpackItemList(){
        return getList(0x25C9);
    }
    
    // Gets a word of SIZE bytes stored in OFFSET.
    unsigned int getWord(unsigned short OFFSET, unsigned char SIZE){
        unsigned int res = 0;
        for(int i = 0; i < SIZE; i++){
            res |= ((unsigned char)data[OFFSET+i] << (8 * (SIZE-i-1)));
        }
        return res;
    }

    // Returns the offset of the given box number.
    
    static unsigned short getPokemonBoxOffset(unsigned char box){
        unsigned char section = (box > 6) + 1;
        unsigned short OFFSET =
            // Get the offset of the section of boxes
            // Boxes are stored in 2 sections; one in 0x2000, other in 0x4000.
            ( 0x2000 + (0x2000 * section) )
            // Get the offset of the box
            // Every box contains 462 bytes of data, don't actually remember what ( (box-1) - (6*(section-1))) is doing
            + ( 0x462 * ( (box-1) - (6*(section-1))));
        return OFFSET;
    }

    // Returns a Pokemon Box stored in OFFSET. The byte in OFFSET is the count of pokemon in the box,
    // and pokemon nicknames and ot names are stored separately from the pokemons themselves, although still
    // inside the box
    PokemonBox getPokemonBoxByOffset(unsigned short OFFSET){
        PokemonBox res;
        res.count = data[OFFSET];
        res.pokemonList = (PokemonInBoxData*)malloc(res.count*sizeof(PokemonInBoxData));
        res.pokemonNicknames.reserve(res.count);
        res.otNames.reserve(res.count);
        for(int i = 0; i < res.count; i++){
            res.pokemonList[i] = getPokemonInBoxData(
                // Each box pokemon contains 0x21 bytes of data
                OFFSET + (0x21 * i)
                // There is a separation of 0x16 bytes between the OFFSET of the box and the actual pokemons
                + 0x16
            );
            res.otNames.push_back(PkmStringConverter::decodeString(
                // OT names are stored 0x2AA bytes after the OFFSET, each name occupies a length of 0xB. bytes.
                readString(OFFSET + 0x2AA + (0xB*i), 0xB)));

            res.pokemonNicknames.push_back(PkmStringConverter::decodeString(
                // Pokemon nicknames are stored 0x386 bytes after the OFFSET, and each nickname occupies a length of 0xB bytes.
                readString(OFFSET + 0x386 + (0xB*i), 0xB)));
        }
        return res;
    }

    // Returns the pokemon box number 'box' of the player.
    PokemonBox getPokemonBox(unsigned char box){
        return getPokemonBoxByOffset(getPokemonBoxOffset(box));
    }

    // Returns a pokemon stored in a box in the offset OFFSET.
    PokemonInBoxData getPokemonInBoxData(unsigned short OFFSET){
        PokemonInBoxData res;
        res.speciesId = data[OFFSET];
        res.hp = getWord(OFFSET+0x1, 2);
        res.level = data[OFFSET+0x3];
        res.statusCondition = data[OFFSET+0x4];
        res.type1 = data[OFFSET+0x5];
        res.type2 = data[OFFSET+0x6];
        res.catchRate = data[OFFSET+0x7];
        res.move1Index = data[OFFSET+0x8];
        res.move2Index = data[OFFSET+0x9];
        res.move3Index = data[OFFSET+0xA];
        res.move4Index = data[OFFSET+0xB];
        res.originalTrainerId = getWord(OFFSET+0xC,2);
        res.expPoints = getWord(OFFSET+0xE,3);
        res.hpEv = getWord(OFFSET+0x11,2);
        res.attackEv = getWord(OFFSET+0x13,2);
        res.defenseEv = getWord(OFFSET+0x15,2);
        res.speedEv = getWord(OFFSET+0x17,2);
        res.specialEv = getWord(OFFSET+0x19,2);
        res.ivData = getWord(OFFSET+0x1B,2);
        res.move1pp = data[OFFSET+0x1D];
        res.move2pp = data[OFFSET+0x1E];
        res.move3pp = data[OFFSET+0x1F];
        res.move4pp = data[OFFSET+0x20];
        return res;
    }

    // Same as above, but for a pokemon in the party. This distinction is needed because pokemons in parties 
    // have some extra data.
    PokemonInPartyData getPokemonInPartyData(unsigned short OFFSET){
        PokemonInPartyData res;
        res.boxData = getPokemonInBoxData(OFFSET);
        res.curLevel = data[OFFSET+0x21];
        res.maxHp = getWord(OFFSET+0x22,2);
        res.attack = getWord(OFFSET+0x24,2);
        res.defense = getWord(OFFSET+0x26,2);
        res.speed = getWord(OFFSET+0x28,2);
        res.special = getWord(OFFSET+0xA,2);
        return res;
    }

    // Returns a Pokemon Party stored in OFFSET. The byte in OFFSET is the count of pokemon in the party,
    // and pokemon nicknames and ot names are stored separately from the pokemons themselves, although still
    // inside the party
    PokemonParty getPokemonPartyByOffset(unsigned short OFFSET){
        PokemonParty res;
        res.count = data[OFFSET];
        res.pokemonList = (PokemonInPartyData *)malloc(res.count * sizeof(PokemonInPartyData));
        res.otNames.reserve(res.count);
        res.pokemonNicknames.reserve(res.count);
        for(int i = 0; i < res.count; i++){
            res.pokemonList[i] = getPokemonInPartyData(
                OFFSET + (0x2C * i) + 0x8
            );
            res.otNames.push_back(PkmStringConverter::decodeString(readString(OFFSET + 0x110 + (0xB*i), 0xB)));
            res.pokemonNicknames.push_back(PkmStringConverter::decodeString(readString(OFFSET + 0x152 + (0xB*i), 0xB)));
        }

        return res;
    }

    PokemonParty getTrainerParty(){
        return getPokemonPartyByOffset(0x2F2C);
    }

    GameOptions getGameOptions(){
        unsigned short OFFSET = 0x2601;
        uchar optionData = data[OFFSET];
        GameOptions res;
        std::bitset<sizeof(optionData)*8> optionBits(optionData);
        res.textSpeed = optionData & 0b111;
        res.stereoSound = optionBits[4];
        res.battleStyleSet = optionBits[6];
        res.battleEffectsOff = optionBits[7];
        return res;
    }

    std::string getPlayerName(){
        unsigned short OFFSET = 0x2598;
        return PkmStringConverter::decodeString(readString(OFFSET, 10));
    }

    uchar getPlayerStarter(){
        unsigned short OFFSET = 0x29C3;
        return data[OFFSET];
    }

    std::string getRivalName(){
        unsigned short OFFSET = 0x25F6;
        return PkmStringConverter::decodeString(readString(OFFSET, 10));
    }

    uchar getRivalStarter(){
        unsigned short OFFSET = 0x29C1;
        return data[OFFSET];
    }

    unsigned short getPlayerId(){
        unsigned short OFFSET = 0x2605;
        return (( (unsigned short)(uchar)data[OFFSET] ) << 8) | (uchar)data[OFFSET+1];
    }

    uchar getHallOfFameRecordCount(){
        unsigned short OFFSET = 0x284E;
        return data[OFFSET];
    }

    std::bitset<8> getBadges(){
        unsigned short OFFSET = 0x2602;
        return (std::bitset<8>(data[OFFSET]));
    }

    PlayTime getPlayTime(){
        unsigned short OFFSET = 0x2CED;
        PlayTime res;
        res.hours = data[OFFSET];
        res.maxedOut = data[OFFSET+1];
        res.minutes = data[OFFSET+2];
        res.seconds = data[OFFSET+3];
        res.frames = data[OFFSET+4];
        return res;
    }

    uchar getChecksumCalc(unsigned int LOWER_BOUND, unsigned int HIGH_BOUND){
        uchar res = 255;
        for(;LOWER_BOUND <= HIGH_BOUND; LOWER_BOUND++){
            res -= (uchar)data[LOWER_BOUND];
        }
        return res;
    }

    uchar getMainChecksum(){
        unsigned short OFFSET = 0x3523;
        return data[OFFSET];
    }

    void log(std::string msg1, std::string msg2="", std::string msg3="", std::string msg4="", std::string msg5=""){
        if(debugMode){
            std::cout << msg1 << " " << msg2 << " " << msg3 << " " << msg4 << " " << msg5 << std::endl;
        }
    }

    void logInline(std::string msg1, std::string msg2="", std::string msg3="", std::string msg4="", std::string msg5=""){
        if(debugMode){
            std::cout << msg1 << " " << msg2 << " " << msg3 << " " << msg4 << " " << msg5;
        }
    }
    
};

#endif