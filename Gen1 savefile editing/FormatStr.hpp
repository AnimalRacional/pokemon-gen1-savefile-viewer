#ifndef FORMATSTR_CPP_I
#define FORMATSTR_CPP_I
#include <string>

class FormatStr{
public:
    static std::string getPokemon(unsigned char index, std::string ending = ""){
        return std::to_string(index+1) + " " + PkmStringConverter::getPokemonName(index) + ending;
    }
    static std::string getCoolPokemonData(PokemonInBoxData pkm){
        return PkmStringConverter::getPokemonNameById(pkm.speciesId) + " lvl " + std::to_string(dispChar(pkm.level));
    }

    static std::string getCoolPokemon(PokemonInBoxData pkm, std::string nickname, std::string originalTrainer){
        return nickname + ", the " + FormatStr::getCoolPokemonData(pkm) + " OT: " + originalTrainer;
    }

    static std::string getCoolPokemonData(PokemonInPartyData pkm){
        return PkmStringConverter::getPokemonNameById(pkm.boxData.speciesId) + " lvl " + std::to_string(dispChar(pkm.curLevel));
    }

    static std::string getCoolPokemon(PokemonInPartyData pkm, std::string nickname, std::string originalTrainer){
        return nickname + ", the " + FormatStr::getCoolPokemonData(pkm) + " OT: " + originalTrainer;
    }

    static std::string getPokemonById(unsigned char index, std::string ending = ""){
        return std::to_string(index+1) + " " + PkmStringConverter::getPokemonNameById(index) + ending;
    }
    static std::string boolToSeen(bool i){ return i ? "Seen" : "Not Seen"; }
    static std::string boolToCaught(bool i){ return i ? "Caught" : "Not Caught"; }
    static std::string boolToGot(bool i){ return i ? "Got" : "Missing"; }

    static unsigned short dispChar(char a){
        return (unsigned short)a;
    }

    static unsigned short dispChar(uchar a){
        return (unsigned short)a;
    }

    static std::string toLowerStr(std::string val){
        std::string res = "";
        for(int i = 0; i < val.length(); i++){
            res += tolower(val[i]);
        }
        return res;
    }

    static std::string toGoodLooking(std::string val){
        std::string res = "";
        res += toupper(val[0]);
        for(int i = 1; i < val.length(); i++){
            char toAdd = val[i];
            if(val[i-1] == ' '){
                toAdd = toupper(val[i]);
            }
            res += toAdd;
        }
        return res;
    }
};

#endif