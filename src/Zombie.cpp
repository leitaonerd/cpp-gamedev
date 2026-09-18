#include "Zombie.h"
#include "GameObject.h"
#include "SpriteRenderer.h"

Zombie::Zombie(GameObject& associated) : Component(associated), hitpoints(100) {
    SpriteRenderer* sprite = new SpriteRenderer(associated, "img/Enemy.png", 3, 2); //3 linhas 2 colunas
    sprite->SetFrame(1);
    associated.AddComponent(sprite);
}

void Zombie::Damage(int damage) {
    hitpoints -= damage;
    
    if (hitpoints <= 0) {
        //template busca o ponteiro do SpriteRenderer
        SpriteRenderer* sprite = associated.GetComponent<SpriteRenderer>();
        if (sprite != nullptr) {
            sprite->SetFrame(5);
        }
    }
}

void Zombie::Update(float dt) {
    //mudar depois
    Damage(1);
}

void Zombie::Render() {
}