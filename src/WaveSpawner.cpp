#include "WaveSpawner.h"
#include "GameObject.h"
#include "Zombie.h"
#include "Game.h"
#include <cstdlib> // para rand()

WaveSpawner::WaveSpawner(GameObject& associated, float spawnInterval) 
    : Component(associated), spawnInterval(spawnInterval) {}

void WaveSpawner::Update(float dt) {
    waveTimer.Update(dt);

    if (waveTimer.Get() >= spawnInterval) {
        waveTimer.Restart();

        GameObject* zombieObj = new GameObject();
        
        //posição aleatória
        zombieObj->box.x = rand() % 1200;
        zombieObj->box.y = rand() % 900;

        Zombie* zombie = new Zombie(*zombieObj);
        zombieObj->AddComponent(zombie);

        Game::GetInstance().GetState().AddObject(zombieObj);
    }
}

void WaveSpawner::Render() {
}