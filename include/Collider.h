#pragma once
#include "Component.h"
#include "Vec2.h"
#include "Rect.h"

class Collider : public Component {
private:
    Vec2 scale;
    Vec2 offset;

public:
    Rect box;

    Collider(GameObject& associated, Vec2 scale = {1, 1}, Vec2 offset = {0, 0});
    
    void Update(float dt) override;
    void Render() override;
    
    void SetScale(Vec2 scale);
    void SetOffset(Vec2 offset);
};