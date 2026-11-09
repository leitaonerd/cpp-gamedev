#pragma once
#include "Component.h"
#include "Timer.h"
#include "Vec2.h"
#include "Sound.h"

class AIController : public Component {
private:
    enum AIState { MOVING, RESTING };
    AIState state;
    Timer restTimer;
    Vec2 destination;

    int hp;
    bool isDead;
    Timer deathTimer;
    Sound deathSound;

public:
    static int npcCounter; 

    AIController(GameObject& associated);
    ~AIController();

    void Update(float dt) override;
    void Render() override;
    
    void NotifyCollision(GameObject& other) override;
    void Damage(int damage);
};