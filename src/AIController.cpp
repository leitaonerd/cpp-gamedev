#include "AIController.h"
#include "Character.h"
#include "Bullet.h"
#include "Game.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Collider.h"

int AIController::npcCounter = 0;

AIController::AIController(GameObject& associated) 
    : Component(associated), state(RESTING), hp(100), isDead(false) {

    SpriteRenderer* sprite = new SpriteRenderer(associated, "assets/img/Enemy.png", 3, 2);
    associated.AddComponent(sprite);

    Animator* animator = new Animator(associated);
    animator->AddAnimation("walking", Animation(0, 3, 10.0f));
    animator->AddAnimation("dead", Animation(5, 5, 0.0f));
    associated.AddComponent(animator);
    animator->SetAnimation("walking");

    associated.AddComponent(new Collider(associated));

    deathSound.Open("assets/audio/Dead.wav");
    
    npcCounter++;
}

AIController::~AIController() {
    npcCounter--;
}

void AIController::Damage(int damage) {
    hp -= damage;
    if (isDead) return;

    if (hp <= 0) {
        isDead = true;
        
        Animator* animator = associated.GetComponent<Animator>();
        if (animator != nullptr) {
            animator->SetAnimation("dead");
        }
        deathSound.Play(1);

        Collider* collider = associated.GetComponent<Collider>();
        if (collider != nullptr) {
            associated.RemoveComponent(collider);
        }
    }
}

void AIController::NotifyCollision(GameObject& other) {
    if (isDead) return;

    Bullet* hitBullet = other.GetComponent<Bullet>();
    if (hitBullet != nullptr && !hitBullet->targetsPlayer) {
        Damage(hitBullet->GetDamage());
    }
}

void AIController::Update(float dt) {
    if (isDead) {
        deathTimer.Update(dt);
        if (deathTimer.Get() >= 5.0f) {
            associated.RequestDelete();
        }
        return; 
    }

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