#ifndef PLAYTIME_CPP_I
#define PLAYTIME_CPP_I

#include <string>
struct PlayTime{
    unsigned char hours;
    unsigned char minutes;
    unsigned char seconds;
    unsigned char frames;
    bool maxedOut;

    std::string getPlaytimeString(std::string frameSeparator = " "){
        return std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds) + frameSeparator + std::to_string(frames) + " frames";
    }

    std::string getIsMaxedOutString(){
        return maxedOut ? "Is Maxed Out" : "Isn't Maxed Out";
    }
};

#endif