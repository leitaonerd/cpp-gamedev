#include "Bullet.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include <cmath>

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance)
    : Component(associated), distanceLeft(maxDistance), damage(damage) {

    SpriteRenderer* renderer = new SpriteRenderer(associated, "assets/img/Bullet.png");
    associated.AddComponent(renderer);

    // calcula velocidade a partir do angulo
    float rad = angle * 3.14159265f / 180.0f;
    this->speed = Vec2(std::cos(rad) * speed, std::sin(rad) * speed);

    associated.box.w = 8;
    associated.box.h = 8;
}

void Bullet::Update(float dt) {
    associated.box.x += speed.x * dt;
    associated.box.y += speed.y * dt;
    distanceLeft -= this->speed.Magnitude() * dt;

    if (distanceLeft <= 0) {
        associated.RequestDelete();
    }
}

void Bullet::Render() {}

int Bullet::GetDamage() {
    return damage;
}
