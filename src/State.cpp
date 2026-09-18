#include "State.h"
#include "SpriteRenderer.h"
#include "Zombie.h"
#include <SDL3/SDL.h>

State::State() : quitRequested(false) {
    //novo background
    GameObject* bgObj = new GameObject();
    SpriteRenderer* bgRenderer = new SpriteRenderer(*bgObj, "assets/img/Background.png");
    bgObj->AddComponent(bgRenderer);
    AddObject(bgObj);

    //musica
    music.Open("assets/audio/BGM.wav");
    music.Play();

    //zumbi
    GameObject* zombieObj = new GameObject();
    //posicao qualquer
    zombieObj->box.x = 600.0f;
    zombieObj->box.y = 450.0f;

    Zombie* zombieLogic = new Zombie(*zombieObj);
    zombieObj->AddComponent(zombieLogic);
    //coloca no gerenciador de State
    AddObject(zombieObj);
}

State::~State() {
    objectArray.clear(); //unique_pointer cuida do resto
}

void State::LoadAssets(){
    //tirar depois do construtor e colocar aqui
}

void State::AddObject(GameObject* go) {
    //constroi o unique_ptr in place
    objectArray.emplace_back(go);
}

void State::Update(float dt){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if(event.type == SDL_EVENT_QUIT){
            quitRequested = true;
        }
    }

    //1) percorre o vetor chamando o Update dos mesmos
    for (int i = 0; i < objectArray.size(); i++){
        objectArray[i]->Update(dt);
    }

    //2) percorre o array testando se algum GameObject morreu
    for (int i = 0; i < objectArray.size(); i++){
        if (objectArray[i]->IsDead()) {
            
            objectArray.erase(objectArray.begin() + i); //remove do array usando begin() + i
            i--; //ajuste de indice por causa do shift de retirar
        }
    }
}

void State::Render(){
    for(int i = 0; i < objectArray.size(); i++){
        objectArray[i]->Render();
    }
}

bool State::QuitRequested(){
    return quitRequested;
}