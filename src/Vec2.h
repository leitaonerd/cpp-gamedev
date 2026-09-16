#pragma once

class Vec2{
public:
    float x;
    float y;

    Vec2();
    Vec2(float x, float y);

    Vec2 GetRotated(float angle) const;
    Vec2 operator+(const Vec2& rhs) const;
    Vec2 operator-(const Vec2& rhs) const;
    Vec2 operator*(const float rhs) const;
    
    float Magnitude() const;
    Vec2 GetNormalized() const;
    float Distance(const Vec2& dst) const;
    float Inclination() const;
    float Inclination(const Vec2& dst) const;
};