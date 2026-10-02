#pragma once
#include "Component.h"
#include "Sound.h"

class Zombie : public Component {
private:
    int hitpoints;
    bool isDead = false;
    Sound deathSound;

public:
    Zombie(GameObject& associated);
    
    
    void Damage(int damage);
    void Update(float dt) override;
    void Render() override;
};