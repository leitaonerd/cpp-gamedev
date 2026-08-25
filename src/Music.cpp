#include "Music.h"
#include "Game.h"
#include <iostream>

Music::Music(){
    audio = nullptr;
    track = nullptr;
}

Music::Music(std::string file){
    audio = nullptr;
    track = nullptr;
    Open(file);
}

Music::~Music(){
    if(IsOpen()){
        Stop(0);
        if(track) MIX_DestroyTrack(track); 
        if(audio) MIX_DestroyAudio(audio); 
    }
}

void Music::Play(int times){
    if(IsOpen()){
        SDL_PropertiesID props = SDL_CreateProperties();
        SDL_SetNumberProperty(props, MIX_PROP_PLAY_LOOPS_NUMBER, times);
        
        MIX_PlayTrack(track, props);
        
        SDL_DestroyProperties(props);
    } else{
        std::cerr << "Nenhuma musica carregada. Audio nao pode ser reproduzido" << std::endl;
    }
}

void Music::Stop(int msToStop){
    if(track){
        MIX_StopTrack(track, msToStop);
    }
}

void Music::Open(std::string file){
    MIX_Mixer* mixer = Game::GetInstance().GetMixer();

    //true pré-decodifica o arquivo de audio na memória pra ter um playback
    audio = MIX_LoadAudio(mixer, file.c_str(), true);

    if(audio == nullptr){
        std::cerr << "MIX_LoadAudio Error: " << SDL_GetError() << std::endl;
        return;
    }

    //cria uma track no mixer e faz o assign do arquivo de audio pra ela
    track = MIX_CreateTrack(mixer);
    MIX_SetTrackAudio(track, audio);
}

bool Music::IsOpen() {
    return audio != nullptr;
}