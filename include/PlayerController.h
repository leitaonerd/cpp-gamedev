#pragma once
#include "Component.h"
#include <memory>

class PlayerController : public Component {
private:
    std::weak_ptr<GameObject> character;

public:
    PlayerController(GameObject& associated);
    void Update(float dt) override;
    void Render() override;
    void SetCharacter(std::weak_ptr<GameObject> newCharacter);
};