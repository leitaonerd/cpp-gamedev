#pragma once
#include "Component.h"
#include "Command.h"
#include "Timer.h"
#include <queue>
#include <memory>
#include <string>

class Character : public Component {
private:
    std::weak_ptr<GameObject> gun;
    std::queue<Command> taskQueue;
    Vec2 speed;
    float linearSpeed;
    int hp;
    Timer deathTimer;
    bool facingLeft;

public:
    static Character* player;

    Character(GameObject& associated, std::string sprite);
    ~Character();
    void Start() override;
    void Update(float dt) override;
    void Render() override;
    void Issue(Command task);
};