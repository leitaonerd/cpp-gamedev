#include "State.h"
#include <SDL3/SDL.h>

State::State() : bg("assets/img/Background.png"), music("assets/audio/BGM.wav"){
    quitRequested = false;

    music.Play(-1);
}

void State::LoadAssets(){
    //tirar depois do construtor e colocar aqui
}

void State::Update(float dt){
    SDL_Event event;

    while(SDL_PollEvent(&event)){
        if(event.type == SDL_EVENT_QUIT){
            quitRequested = true;
        }
    }
}

void State::Render(){
    bg.Render(0.0f, 0.0f);
}

bool State::QuitRequested(){
    return quitRequested;
}