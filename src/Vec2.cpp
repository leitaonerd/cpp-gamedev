#include "Vec2.h"
#include <cmath>

Vec2::Vec2() : x(0), y(0) {}
Vec2::Vec2(float x, float y) : x(x), y(y) {}

//rotação baseada na matriz de rotação especificada no PDF
Vec2 Vec2::GetRotated(float angle) const{
    float x_prime = x * std::cos(angle) - y * std::sin(angle);
    float y_prime = y * std::cos(angle) + x * std::sin(angle);
    return Vec2(x_prime, y_prime);
}

Vec2 Vec2::operator+(const Vec2& rhs) const { return Vec2(x + rhs.x, y + rhs.y); }
Vec2 Vec2::operator-(const Vec2& rhs) const { return Vec2(x - rhs.x, y - rhs.y); }
Vec2 Vec2::operator*(const float rhs) const { return Vec2(x * rhs, y * rhs); }

float Vec2::Magnitude() const { return std::sqrt(x * x + y * y); }

Vec2 Vec2::GetNormalized() const{
    float mag = Magnitude();
    if (mag == 0) return Vec2(0, 0); //prevenção de divisão por zero
    return Vec2(x / mag, y / mag);
}

float Vec2::Distance(const Vec2& dst) const { return (*this - dst).Magnitude(); }

float Vec2::Inclination() const { return std::atan2(y, x); }

float Vec2::Inclination(const Vec2& dst) const { return (dst - *this).Inclination(); }