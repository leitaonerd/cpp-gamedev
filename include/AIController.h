#pragma once
#include "Component.h"
#include "Timer.h"
#include "Vec2.h"

class AIController : public Component {
private:
    enum AIState { MOVING, RESTING };
    AIState state;
    Timer restTimer;
    Vec2 destination;

public:
    static int npcCounter;

    AIController(GameObject& associated);
    ~AIController();

    void Update(float dt) override;
    void Render() override;
};