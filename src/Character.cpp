#include "Character.h"
#include "GameObject.h"
#include "Gun.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Animation.h"
#include "Game.h"

Character* Character::player = nullptr;

Character::Character(GameObject& associated, std::string sprite)
    : Component(associated), speed(0, 0), linearSpeed(200.0f), hp(100), facingLeft(false) {
    // sprite do personagem
    SpriteRenderer* renderer = new SpriteRenderer(associated, sprite, 3, 4);
    associated.AddComponent(renderer);


    // animações
    Animator* animator = new Animator(associated);
    animator->AddAnimation("idle_right", Animation(0, 0, 0.0f, SDL_FLIP_NONE));
    animator->AddAnimation("idle_left", Animation(0, 0, 0.0f, SDL_FLIP_HORIZONTAL));
    animator->AddAnimation("walking_right", Animation(0, 3, 0.1f, SDL_FLIP_NONE));
    animator->AddAnimation("walking_left", Animation(0, 3, 0.1f, SDL_FLIP_HORIZONTAL));
    animator->AddAnimation("dead", Animation(0, 0, 0.0f, SDL_FLIP_NONE));
    associated.AddComponent(animator);
    animator->SetAnimation("idle_right");

    // registra instância global do jogador
    player = this;
}

Character::~Character() {
    player = nullptr;
}

void Character::Start() {
    // cria a arma como objeto separado no State
    GameObject* gunObj = new GameObject();
    Gun* gunComp = new Gun(*gunObj, std::weak_ptr<GameObject>());
    gunObj->AddComponent(gunComp);
    Game::GetInstance().GetState().AddObject(gunObj);

    // guarda referência fraca para a arma
    std::weak_ptr<GameObject> gunWeak = Game::GetInstance().GetState().GetObjectPtr(gunObj);
    gun = gunWeak;
}

void Character::Update(float dt) {
    if (hp <= 0) {
        // animação de morte
        Animator* animator = associated.GetComponent<Animator>();
        if (animator) {
            animator->SetAnimation("dead");
        }
        deathTimer.Update(dt);
        if (deathTimer.Get() >= 1.0f) {
            associated.RequestDelete();
        }
        return;
    }

    // consome fila de comandos
    while (!taskQueue.empty()) {
        Command cmd = taskQueue.front();
        taskQueue.pop();

        std::string suffix = facingLeft ? "_left" : "_right";

        if (cmd.type == Command::MOVE) {
            speed = cmd.pos.GetNormalized() * linearSpeed;

            // orienta animação de movimento
            Animator* animator = associated.GetComponent<Animator>();
            if (animator) {
                animator->SetAnimation("walking" + suffix);
            }
        } else if (cmd.type == Command::SHOOT) {
            auto gunObj = gun.lock();
            if (gunObj) {
                Gun* gunComp = gunObj->GetComponent<Gun>();
                if (gunComp) {
                    gunComp->Shoot(cmd.pos);
                }
            }

            Animator* animator = associated.GetComponent<Animator>();
            if (animator) {
                animator->SetAnimation("idle" + suffix);
            }
        }
    }

    // aplica movimento
    associated.box.x += speed.x * dt;
    associated.box.y += speed.y * dt;

    // atrito para desacelerar suavemente
    speed.x *= 0.90f;
    speed.y *= 0.90f;

    if (speed.x < -0.1f) {
        facingLeft = true;
    } else if (speed.x > 0.1f) {
        facingLeft = false;
    }

    std::string suffix = facingLeft ? "_left" : "_right";

    Animator* animator = associated.GetComponent<Animator>();
    if (animator) {
        if (speed.Magnitude() >= 1.0f) {
            animator->SetAnimation("walking" + suffix);
        } else {
            animator->SetAnimation("idle" + suffix);
        }
    }
}

void Character::Render() {}

void Character::Issue(Command task) {
    taskQueue.push(task);
}
