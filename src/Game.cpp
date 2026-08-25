#include "Game.h"
#include <SDL3_image/SDL_image.h>
#include <iostream>

Game* Game::instance = nullptr;

Game& Game::GetInstance(){
    if(instance == nullptr){
        instance = new Game("Nome - [Matrícula]", 1200, 900);
    }
    return *instance;
}

Game::Game(std::string title, int width, int height){
    if(instance != nullptr){
        std::cerr << "Erro na lógica do jogo. Instância de jogo já existe" << std::endl;
        //erro tratar depois
        return;
    }
    instance = this;    

    //core SDL3 subsystems
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0){
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    }
    //SDL_image loaders
    if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0){
        std::cerr << "IMG_Init Error: " << SDL_GetError() << std::endl;
    }
    //SDL3_mixer device
    mixer = MIX_CreateMixerDevice(0, nullptr);
    if(mixer == nullptr){
        std::cerr << "Mixer Error: " << SDL_GetError() << std::endl;
    }
    //SDL3 window
    window = SDL_CreateWindow(title.c_str(), width, height, 0);
    if(window == nullptr){
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    }
    //SDL3 renderer
    renderer = SDL_CreateRenderer(window, nullptr);
    if(renderer == nullptr){
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    }

    state = new State();
}

Game::~Game(){
    delete state;
    if(mixer) MIX_DestroyMixer(mixer);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit(); 
}

State& Game::GetState(){
    return *state;
}

SDL_Renderer* Game::GetRenderer(){
    return renderer;
}

void Game::Run(){
    while (!state->QuitRequested()) {
        state->Update(0.0f);
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(33); //30 fps
    }
}
