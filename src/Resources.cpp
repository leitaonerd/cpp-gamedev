#include "Resources.h"
#include "Game.h"
#include <SDL3_image/SDL_image.h>
#include <iostream>

//inicializao doq eh estatico fora da classe
std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, MIX_Audio*> Resources::audioTable;

SDL_Texture* Resources::GetImage(std::string file) {
    auto it = imageTable.find(file);
    
    if (it == imageTable.end()) {
        SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
        SDL_Texture* texture = IMG_LoadTexture(renderer, file.c_str());
        
        if (texture == nullptr) {
            std::cerr << "Erro ao carregar textura: " << SDL_GetError() << std::endl;
            return nullptr;
        }
        
        imageTable[file] = texture;
        return texture;
    }
    
    //se ja existe retorna o ponteiro do cache
    return it->second;
}

MIX_Audio* Resources::GetAudio(std::string file) {
    auto it = audioTable.find(file);

    if (it == audioTable.end()) {
        MIX_Mixer* mixer = Game::GetInstance().GetMixer();
        MIX_Audio* audio = MIX_LoadAudio(mixer, file.c_str(), true);
        
        if (audio == nullptr) {
            std::cerr << "Erro ao carregar audio: " << SDL_GetError() << std::endl;
            return nullptr;
        }
        
        audioTable[file] = audio;
        return audio;
    }
    
    return it->second;
}

void Resources::ClearImages() {
    for (auto it = imageTable.begin(); it != imageTable.end(); it++) {
        if (it->second != nullptr) {
            SDL_DestroyTexture(it->second);
        }
    }
    imageTable.clear();
}

void Resources::ClearAudios() {
    for (auto it = audioTable.begin(); it != audioTable.end(); it++) {
        if (it->second != nullptr) {
            MIX_DestroyAudio(it->second);
        }
    }
    audioTable.clear();
}

void Resources::ClearAll() {
    ClearImages();
    ClearAudios();
}