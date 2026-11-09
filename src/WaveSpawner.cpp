#include "WaveSpawner.h"
#include "GameObject.h"
#include "Zombie.h"
#include "Game.h"
#include "Camera.h"
#include "AIController.h"
#include <cstdlib> // Para rand()
#include <cmath>

WaveSpawner::WaveSpawner(GameObject& associated) 
    : Component(associated), zombieCounter(0), currentWave(0) {
    
    waves.push_back(Wave(3, 2.0f)); // Wave 0: 3 zumbis, 1 a cada 2 seg
    waves.push_back(Wave(5, 1.5f)); // Wave 1: 5 zumbis, 1 a cada 1.5 seg
    waves.push_back(Wave(10, 1.0f)); // Wave 2: 10 zumbis, 1 a cada 1 seg
}

void WaveSpawner::Update(float dt) {
    if (currentWave >= waves.size()) {
        associated.RequestDelete();
        return;
    }

    zombieCooldownTimer.Update(dt);

    Wave& wave = waves[currentWave];

    if (zombieCounter < wave.zombies) {
        if (zombieCooldownTimer.Get() >= wave.cooldown) {
            zombieCooldownTimer.Restart();
            
            GameObject* enemyObj = new GameObject();
            
            float randomAngle = (rand() % 360) * (3.14159f / 180.0f);
            
            float spawnDistance = 400.0f; 
            enemyObj->box.x = Camera::pos.x + 600 + (std::cos(randomAngle) * spawnDistance); // 600 é meio da tela
            enemyObj->box.y = Camera::pos.y + 450 + (std::sin(randomAngle) * spawnDistance); // 450 é meio da tela

            // 30% NPC / 70% zumbi
            if (rand() % 100 < 30) {
                AIController* npc = new AIController(*enemyObj);
                enemyObj->AddComponent(npc);
            } else {
                Zombie* zombie = new Zombie(*enemyObj);
                enemyObj->AddComponent(zombie);
            }

            Game::GetInstance().GetState().AddObject(enemyObj);
            
            zombieCounter++;
        }
    } 
    else if (Zombie::zombieCount == 0 && AIController::npcCounter == 0) {
        currentWave++;
        zombieCounter = 0;
    }
}

void WaveSpawner::Render() { }