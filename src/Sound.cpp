#include "Sound.h"
#include "Game.h"
#include <iostream>

Sound::Sound() {
    audio = nullptr;
    track = nullptr;
}

Sound::Sound(std::string file) {
    audio = nullptr;
    track = nullptr;
    Open(file);
}

Sound::~Sound() {
    if(IsOpen()) {
        Stop();
        if(track) MIX_DestroyTrack(track); 
        if(audio) MIX_DestroyAudio(audio); 
    }
}

void Sound::Play(int times) {
    if(IsOpen()) {
        SDL_PropertiesID props = SDL_CreateProperties();
        
        // Se times = 1, loops = 0 (toca apenas a vez original)
        SDL_SetNumberProperty(props, MIX_PROP_PLAY_LOOPS_NUMBER, times - 1);
        
        MIX_PlayTrack(track, props);
        
        SDL_DestroyProperties(props);
    } else {
        std::cerr << "Nenhum som carregado. Audio nao pode ser reproduzido" << std::endl;
    }
}

void Sound::Stop() {
    if(track) {
        // Efeitos sonoros param instantaneamente (0 ms)
        MIX_StopTrack(track, 0); 
    }
}

void Sound::Open(std::string file) {
    MIX_Mixer* mixer = Game::GetInstance().GetMixer();

    // true pré-decodifica o arquivo de audio na memória (ideal para efeitos sonoros rápidos)
    audio = MIX_LoadAudio(mixer, file.c_str(), true);

    if(audio == nullptr) {
        std::cerr << "MIX_LoadAudio Error: " << SDL_GetError() << std::endl;
        return;
    }

    track = MIX_CreateTrack(mixer);
    MIX_SetTrackAudio(track, audio);
}

bool Sound::IsOpen() {
    return audio != nullptr;
}