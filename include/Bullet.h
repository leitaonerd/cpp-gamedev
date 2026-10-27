#pragma once
#include "Component.h"
#include "Vec2.h"

class Bullet : public Component {
private:
    Vec2 speed;
    float distanceLeft;
    int damage;

public:
    Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance);
    void Update(float dt) override;
    void Render() override;
    int GetDamage();
};