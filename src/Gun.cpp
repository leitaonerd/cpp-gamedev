#include "Gun.h"
#include "GameObject.h"
#include "Bullet.h"
#include "SpriteRenderer.h"
#include "Game.h"
#include <cmath>
#include <iostream>

Gun::Gun(GameObject& associated, std::weak_ptr<GameObject> character)
    : Component(associated), character(character), cooldownState(0), angle(0.0f) {
    // sprite da arma
    SpriteRenderer* renderer = new SpriteRenderer(associated, "assets/img/Gun.png", 3, 2);
    associated.AddComponent(renderer);

    shotSound.Open("assets/audio/BGM.wav");
    reloadSound.Open("assets/audio/BGM.wav");
}

void Gun::Update(float dt) {
    cdTimer.Update(dt);

    auto charObj = character.lock();
    if (!charObj) {
        associated.RequestDelete();
        return;
    }

    // sincroniza a posição da arma com o personagem
    Vec2 center = charObj->box.Center();
    associated.box.x = center.x - associated.box.w / 2.0f;
    associated.box.y = center.y - associated.box.h / 2.0f;

    // aplica deslocamento na direção do ângulo
    float rad = angle * 3.14159265f / 180.0f;
    associated.box.x += std::cos(rad) * 12.0f;
    associated.box.y += std::sin(rad) * 12.0f;

    // máquina de estados de cooldown (0 a 3)
    SpriteRenderer* sprite = associated.GetComponent<SpriteRenderer>();
    SDL_FlipMode flip = (angle > 90.0f || angle < -90.0f) ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
    if (sprite) {
        sprite->SetFlip(flip); 
    }
    associated.SetAngleDeg(angle);
    
    if(cooldownState == 0){
        // estado ocioso: garante que fica no primeiro quadro
        if (sprite) sprite->SetFrame(0);
        
    } else if(cooldownState == 1){
        // disparo efetuado: anima os quadros 1 e 2 durante 0.1s
        if(sprite){
            int frame = 1 + static_cast<int>((cdTimer.Get() / 0.1f) * 2.0f);
            if (frame > 2) frame = 2;
            sprite->SetFrame(frame);
        }

        if(cdTimer.Get() >= 0.1f){
            cooldownState = 2;
            cdTimer.Restart();
            reloadSound.Play(1);
        }
        
    } else if(cooldownState == 2){
        // recarga (pump-action): anima os quadros 3, 4 e 5 durante 0.3s
        if(sprite){
            int frame = 3 + static_cast<int>((cdTimer.Get() / 0.3f) * 3.0f);
            if (frame > 5) frame = 5;
            sprite->SetFrame(frame);
        }

        if(cdTimer.Get() >= 0.3f){
            cooldownState = 3;
            cdTimer.Restart();
        }
        
    } else if(cooldownState == 3){
        // fim da recarga, pronto para atirar novamente
        cooldownState = 0;
        if (sprite) sprite->SetFrame(0);
    }
}

void Gun::Render() {}

void Gun::Shoot(Vec2 target) {
    if (cooldownState != 0) {
        return;
    }

    // calcula ângulo para o alvo
    Vec2 pos = associated.box.Center();
    Vec2 dir = target - pos;
    angle = dir.Inclination() * 180.0f / 3.14159265f;

    shotSound.Play(1);

    // instancia projétil
    GameObject* bulletObj = new GameObject();
    bulletObj->box.x = pos.x - 4;
    bulletObj->box.y = pos.y - 4;

    float speed = 500.0f;
    int damage = 100;
    float maxDistance = 600.0f;

    Bullet* bullet = new Bullet(*bulletObj, angle, speed, damage, maxDistance);
    bulletObj->AddComponent(bullet);

    Game::GetInstance().GetState().AddObject(bulletObj);

    // entra em cooldown
    cooldownState = 1;
    cdTimer.Restart();
}