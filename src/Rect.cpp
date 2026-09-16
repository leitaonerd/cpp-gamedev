#include "Rect.h"

Rect::Rect() : x(0), y(0), w(0), h(0) {}
Rect::Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

Vec2 Rect::Center() const{
    return Vec2(x + w / 2.0f, y + h / 2.0f);
}

float Rect::Distance(const Rect& dst) const{
    return Center().Distance(dst.Center());
}

bool Rect::Contains(float pX, float pY) const{
    return (pX >= x && pX <= x + w && pY >= y && pY <= y + h);
}

bool Rect::Contains(const Vec2& p) const{
    return Contains(p.x, p.y);
}

Rect Rect::operator+(const Vec2& rhs) const{
    return Rect(x + rhs.x, y + rhs.y, w, h);
}