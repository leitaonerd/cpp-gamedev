#pragma once
#include "Component.h"
#include "Vec2.h"

class Bullet : public Component {
private:
    Vec2 speed;
    float distanceLeft;
    int damage;

public:
    bool targetsPlayer;
    Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, bool targetsPlayer);
    void Update(float dt) override;
    void Render() override;
    void NotifyCollision(GameObject& other) override;
    int GetDamage();
};