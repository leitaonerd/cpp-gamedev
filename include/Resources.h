#pragma once
#include <string>
#include <unordered_map>
#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>

class Resources {
private:
    static std::unordered_map<std::string, SDL_Texture*> imageTable;
    static std::unordered_map<std::string, MIX_Audio*> audioTable;

public:
    static SDL_Texture* GetImage(std::string file);
    static void ClearImages();

    static MIX_Audio* GetAudio(std::string file);
    static void ClearAudios();

    static void ClearAll();
};