#include "AIController.h"
#include "Character.h"
#include "Bullet.h"
#include "Game.h"

int AIController::npcCounter = 0;

AIController::AIController(GameObject& associated) : Component(associated), state(RESTING) {
    npcCounter++;
}

AIController::~AIController() {
    npcCounter--;
}

void AIController::Update(float dt) {
    if (Character::player == nullptr) {
        return; 
    }

    if (state == RESTING) {
        restTimer.Update(dt);
        
        if (restTimer.Get() >= 2.0f) { 
            destination = Character::player->GetAssociated().box.Center();
            state = MOVING;
        }
    } 
    else if (state == MOVING) {
        Vec2 currentPos = associated.box.Center();
        float distance = currentPos.Distance(destination);

        if (distance <= 5.0f) {
            Vec2 playerPos = Character::player->GetAssociated().box.Center();
            float angle = (playerPos - currentPos).Inclination() * (180.0f / 3.14159265f);

            GameObject* bulletObj = new GameObject();
            bulletObj->box.x = currentPos.x;
            bulletObj->box.y = currentPos.y;
            
            Bullet* bullet = new Bullet(*bulletObj, angle, 300.0f, 10, 800.0f, true);
            bulletObj->AddComponent(bullet);
            Game::GetInstance().GetState().AddObject(bulletObj);

            restTimer.Restart();
            state = RESTING;
        } 
        else {
            Vec2 dir = (destination - currentPos).GetNormalized();
            float speed = 150.0f * dt; 
            associated.box.x += dir.x * speed;
            associated.box.y += dir.y * speed;
        }
    }
}

void AIController::Render() {}