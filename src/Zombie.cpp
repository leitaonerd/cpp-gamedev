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
    animator->AddAnimation("walking", Animation(0, 3, 10.0f));
    animator->AddAnimation("dead", Animation(5, 5, 0.0f));
    
    associated.AddComponent(animator);
    animator->SetAnimation("walking");

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
            animator->SetAnimation("dead");
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
    }
}

void Zombie::Render() {
}