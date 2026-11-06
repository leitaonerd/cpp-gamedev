#define DEBUG
#include "Collider.h"
#include "Camera.h"
#include "Game.h"
#include <SDL3/SDL.h>
#include <cmath>

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset) 
    : Component(associated), scale(scale), offset(offset) {}

void Collider::Update(float dt) {
    // A box do collider assume as dimensões do objeto modificadas pela escala da colisão
    box.w = associated.box.w * scale.x;
    box.h = associated.box.h * scale.y;

    // Atualiza o centro aplicando o offset rotacionado
    Vec2 center = associated.box.Center();
    float angleRad = associated.GetAngleDeg() * (3.14159265359f / 180.0f);
    Vec2 rotatedOffset = offset.GetRotated(angleRad);
    
    box.x = center.x + rotatedOffset.x - (box.w / 2.0f);
    box.y = center.y + rotatedOffset.y - (box.h / 2.0f);
}

void Collider::Render() {
#ifdef DEBUG
    Vec2 center(box.Center());
    SDL_FPoint points[5];
    float angleRad = associated.GetAngleDeg() * (3.14159265359f / 180.0f);

    Vec2 point = (Vec2(box.x, box.y) - center).GetRotated(angleRad) + center - Camera::pos;
    points[0] = {point.x, point.y};
    points[4] = {point.x, point.y};
    
    point = (Vec2(box.x + box.w, box.y) - center).GetRotated(angleRad) + center - Camera::pos;
    points[1] = {point.x, point.y};
    
    point = (Vec2(box.x + box.w, box.y + box.h) - center).GetRotated(angleRad) + center - Camera::pos;
    points[2] = {point.x, point.y};
    
    point = (Vec2(box.x, box.y + box.h) - center).GetRotated(angleRad) + center - Camera::pos;
    points[3] = {point.x, point.y};

    SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, 255);
    SDL_RenderLines(Game::GetInstance().GetRenderer(), points, 5);
#endif
}

void Collider::SetScale(Vec2 scale) { this->scale = scale; }
void Collider::SetOffset(Vec2 offset) { this->offset = offset; }