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

    SpriteRenderer* sprite = new SpriteRenderer(associated, "assets/img/NPC.png", 3, 4);
    associated.AddComponent(sprite);

    Animator* animator = new Animator(associated);
    animator->AddAnimation("walking_right", Animation(0, 9, 0.15f, SDL_FLIP_NONE));
    animator->AddAnimation("walking_left", Animation(0, 9, 0.15f, SDL_FLIP_HORIZONTAL));
    animator->AddAnimation("dead_right", Animation(10, 11, 0.15f, SDL_FLIP_NONE));
    animator->AddAnimation("dead_left", Animation(10, 11, 0.15f, SDL_FLIP_HORIZONTAL));
    associated.AddComponent(animator);
    animator->SetAnimation("walking_right");

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
            animator->SetAnimation(facingLeft ? "dead_left" : "dead_right");
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

            if (playerPos.x < currentPos.x) facingLeft = true;
            else facingLeft = false;
            
            Animator* animator = associated.GetComponent<Animator>();
            if (animator != nullptr) {
                animator->SetAnimation(facingLeft ? "walking_left" : "walking_right");
            }

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

            if (dir.x < -0.1f) {
                facingLeft = true;
            } else if (dir.x > 0.1f) {
                facingLeft = false;
            }

            Animator* animator = associated.GetComponent<Animator>();
            if (animator != nullptr) {
                animator->SetAnimation(facingLeft ? "walking_left" : "walking_right");
            }
            if (animator != nullptr) {
                animator->Update(dt);
            }
        }
    }
}

void AIController::Render() {}