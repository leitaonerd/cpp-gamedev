#pragma once
#include "Vec2.h"

class Rect{
public:
    float x, y, w, h;

    Rect();
    Rect(float x, float y, float w, float h);

    Vec2 Center() const;
    float Distance(const Rect& dst) const;
    bool Contains(float pX, float pY) const;
    bool Contains(const Vec2& p) const;
    
    Rect operator+(const Vec2& rhs) const;
};