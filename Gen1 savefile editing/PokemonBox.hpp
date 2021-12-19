#ifndef POKEMONBOX_CPP_I
#define POKEMONBOX_CPP_I
#include <vector>
#include <string>
struct PokemonInBoxData{
    unsigned char speciesId;
    unsigned short hp;
    unsigned char level;
    unsigned char statusCondition;
    unsigned char type1;
    unsigned char type2;
    unsigned char catchRate;
    unsigned char move1Index;
    unsigned char move2Index;
    unsigned char move3Index;
    unsigned char move4Index;
    unsigned short originalTrainerId;
    unsigned int expPoints;
    unsigned short hpEv;
    unsigned short attackEv;
    unsigned short defenseEv;
    unsigned short speedEv;
    unsigned short specialEv;
    unsigned short ivData;
    unsigned char move1pp;
    unsigned char move2pp;
    unsigned char move3pp;
    unsigned char move4pp;
};

struct PokemonInPartyData{
    PokemonInBoxData boxData;
    unsigned char curLevel;
    unsigned short maxHp;
    unsigned short attack;
    unsigned short defense;
    unsigned short speed;
    unsigned short special;
};

struct PokemonBox{
    unsigned char count;
    PokemonInBoxData *pokemonList;
    std::vector<std::string> otNames;
    std::vector<std::string> pokemonNicknames;
};

struct PokemonParty{
    unsigned char count;
    PokemonInPartyData *pokemonList;
    std::vector<std::string> otNames;
    std::vector<std::string> pokemonNicknames;
};

#endif