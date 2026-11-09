#include "Zombie.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Animation.h"
#include "Collider.h"
#include "Bullet.h"
#include "Character.h"

int Zombie::zombieCount = 0;

Zombie::Zombie(GameObject& associated) : Component(associated), hitpoints(100) {
    SpriteRenderer* sprite = new SpriteRenderer(associated, "assets/img/Enemy.png", 3, 2);
    associated.AddComponent(sprite);

    Animator* animator = new Animator(associated);
    animator->AddAnimation("walking_right", Animation(0, 3, 0.15f, SDL_FLIP_NONE));
    animator->AddAnimation("walking_left", Animation(0, 3, 0.15f, SDL_FLIP_HORIZONTAL));
    animator->AddAnimation("dead_right", Animation(5, 5, 0.15f, SDL_FLIP_NONE));
    animator->AddAnimation("dead_left", Animation(5, 5, 0.15f, SDL_FLIP_HORIZONTAL));
    associated.AddComponent(animator);
    animator->SetAnimation("walking_right");

    associated.AddComponent(new Collider(associated));

    deathSound.Open("assets/audio/Dead.wav");
    zombieCount++;
}


Zombie::~Zombie() {
    zombieCount--; // Decrementa quando o cadáver é removido da memória
}

void Zombie::Damage(int damage) {
    hitpoints -= damage;

    if(isDead){
        return;
    }
    
    if (hitpoints <= 0) {
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

void Zombie::NotifyCollision(GameObject& other) {
    if (isDead) return;

    Bullet* hitBullet = other.GetComponent<Bullet>();
    if (hitBullet != nullptr) {
        Damage(hitBullet->GetDamage());
    }
}

void Zombie::Update(float dt) {
    if (isDead) {
        deathTimer.Update(dt);
        if (deathTimer.Get() >= 5.0f) {
            associated.RequestDelete();
        }
        return;
    }

    if (Character::player != nullptr) {
        Vec2 playerPos = Character::player->GetAssociated().box.Center();
        Vec2 currentPos = associated.box.Center();
        
        Vec2 dir = (playerPos - currentPos).GetNormalized();
        float speed = 80.0f * dt;
        
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

void Zombie::Render() {
}