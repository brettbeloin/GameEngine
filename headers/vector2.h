#pragma once
#include <cmath>

namespace Engine {
    class Vector2 {
      public:
        Vector2() = default;
        Vector2(float x, float y) : x{x}, y{y} {};
        Vector2(float v) : x{v}, y{v} {};

        float   x, y;

        Vector2 operator+(const Vector2 &v) const {
            return Vector2{this->x + v.x, this->y + v.y};
        }

        Vector2 operator-(const Vector2 &v) const {
            return Vector2{this->x - v.x, this->y - v.y};
        }

        Vector2 operator*(const Vector2 &v) const {
            return Vector2{this->x * v.x, this->y * v.y};
        }

        Vector2 operator/(const Vector2 &v) const {
            return Vector2{this->x / v.x, this->y / v.y};
        }

        Vector2 operator+(float v) const {
            return Vector2{this->x + v, this->y};
        }

        Vector2 operator-(float v) const {
            return Vector2{this->x - v, this->y};
        }

        Vector2 operator*(float v) const {
            return Vector2{this->x * v, this->y * v};
        }

        Vector2 operator/(float v) const {
            return Vector2{this->x / v, this->y / v};
        }

        Vector2 &operator+=(const Vector2 &v) {
            this->x += v.x;
            this->y += v.y;
            return *this;
        }

        Vector2 &operator-=(const Vector2 &v) {
            this->x -= v.x;
            this->y -= v.y;
            return *this;
        }

        Vector2 &operator*=(const Vector2 &v) {
            this->x *= v.x;
            this->y *= v.y;
            return *this;
        }

        Vector2 &operator/=(const Vector2 &v) {
            this->x /= v.x;
            this->y /= v.y;
            return *this;
        }

        Vector2 &operator+=(float v) {
            this->x += v;
            this->y += v;
            return *this;
        }

        Vector2 &operator-=(float v) {
            this->x -= v;
            this->y -= v;
            return *this;
        }

        Vector2 &operator*=(float v) {
            this->x *= v;
            this->y *= v;
            return *this;
        }

        Vector2 &operator/=(float v) {
            this->x /= v;
            this->y /= v;
            return *this;
        }

        float LengthSqr() const {
            return (x * x) + (y * y);
        }

        float length() const {
            return std::sqrt(LengthSqr());
        }
    };
}; // namespace Engine
