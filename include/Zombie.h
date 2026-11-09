#pragma once
#include "Component.h"
#include "Sound.h"
#include "Timer.h"

class Zombie : public Component {
private:
    int hitpoints;
    bool isDead = false;
    bool facingLeft = false;
    Timer deathTimer;
    Sound deathSound;

public:
    static int zombieCount;

    Zombie(GameObject& associated);
    ~Zombie();
    
    void Damage(int damage);
    void Update(float dt) override;
    void Render() override;
    void NotifyCollision(GameObject& other) override;
};