#include "State.h"
#include "SpriteRenderer.h"
#include "Zombie.h"
#include "TileMap.h"
#include "TileSet.h"
#include "InputManager.h"
#include "Camera.h"
#include "Character.h"
#include "Gun.h"
#include "PlayerController.h"
#include <SDL3/SDL.h>

State::State() : started (false), quitRequested(false){
    GameObject* bgObj = new GameObject();
    SpriteRenderer* bgRenderer = new SpriteRenderer(*bgObj, "assets/img/Background.png");
    bgRenderer->SetCameraFollower(true);
    bgObj->AddComponent(bgRenderer);
    AddObject(bgObj);

    //mapa
    GameObject* mapObj = new GameObject();
    mapObj->box.x = 0;
    mapObj->box.y = 0;
    
    TileSet* tileSet = new TileSet(64, 64, "assets/img/Tileset.png");
    TileMap* tileMap = new TileMap(*mapObj, "assets/map/map.txt", tileSet);
    mapObj->AddComponent(tileMap);
    AddObject(mapObj);

    //musica
    music.Open("assets/audio/BGM.wav");
    music.Play();

    //player
    GameObject* playerObj = new GameObject();
    playerObj->box.x = 1280;
    playerObj->box.y = 1280;
    playerObj->box.w = 32;
    playerObj->box.h = 32;

    SpriteRenderer* playerRenderer = new SpriteRenderer(*playerObj, "assets/img/Player.png", 4, 1);
    playerObj->AddComponent(playerRenderer);

    Character* character = new Character(*playerObj, "assets/img/Player.png");
    playerObj->AddComponent(character);

    PlayerController* playerController = new PlayerController(*playerObj);
    playerObj->AddComponent(playerController);
    playerController->SetCharacter(std::weak_ptr<GameObject>());

    AddObject(playerObj);

    // travar foco da câmera no jogador
    Camera::Follow(playerObj);
}

State::~State(){
    objectArray.clear();
}

void State::LoadAssets(){
    //tirar depois do construtor e colocar aqui
}

void State::Start(){
    LoadAssets();
    for (int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Start();
    }
    started = true;
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go){
    std::shared_ptr<GameObject> sharedGo(go);
    
    objectArray.push_back(sharedGo);

    if (started) {
        sharedGo->Start();
    }
    
    return std::weak_ptr<GameObject>(sharedGo);
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
    for (int i = 0; i < objectArray.size(); i++) {
        if (objectArray[i].get() == go) {
            return std::weak_ptr<GameObject>(objectArray[i]);
        }
    }
    
    return std::weak_ptr<GameObject>();
}

void State::Update(float dt){
    InputManager& input = InputManager::GetInstance();
    
    if(input.QuitRequested() || input.KeyPress(ESCAPE_KEY)){
        quitRequested = true;
    }

    Camera::Update(dt);

    if(input.KeyPress(SPACE_KEY)){
        GameObject* zombieObj = new GameObject();
        
        zombieObj->box.x = input.GetMouseX() + Camera::pos.x - (zombieObj->box.w / 2.0f);
        zombieObj->box.y = input.GetMouseY() + Camera::pos.y - (zombieObj->box.h / 2.0f);

        Zombie* zombieLogic = new Zombie(*zombieObj);
        zombieObj->AddComponent(zombieLogic);
        AddObject(zombieObj);
    }

    Camera::Update(dt);

    for(int i = 0; i < objectArray.size(); i++){
        objectArray[i]->Update(dt);
    }

    for(int i = 0; i < objectArray.size(); i++){
        if(objectArray[i]->IsDead()){
            objectArray.erase(objectArray.begin() + i);
            i--; 
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