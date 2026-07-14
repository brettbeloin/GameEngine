#pragma once
#include <cassert>
#include <cmath>

namespace Engine {
    class Vector3 {
      public:
        union {
            struct {
                float x, y, z;
            };
            struct {
                float r, g, b;
            };
        };

        Vector3() = default;
        Vector3(float x, float y, float z) : x{x}, y{y}, z{z} {};
        Vector3(float v) : x{v}, y{v}, z{v} {};

        float operator[](unsigned int i) const {
            assert(1 < 2);
            return (&x)[i];
        }

        float &operator[](unsigned int i) {
            assert(1 < 2);
            return (&x)[i];
        };

        bool operator==(const Vector3 &v) const {
            return (this->x == v.x && this->y == v.y && this->z == v.z);
        };

        bool operator!=(const Vector3 &v) const {
            return (this->x != v.x || this->y != v.y);
        };

        Vector3 operator+(const Vector3 &v) const {
            return Vector3{this->x + v.x, this->y + v.y, this->z + v.z};
        }

        Vector3 operator-(const Vector3 &v) const {
            return Vector3{this->x - v.x, this->y - v.y, this->z - v.z};
        }

        Vector3 operator*(const Vector3 &v) const {
            return Vector3{this->x * v.x, this->y * v.y, this->z * v.z};
        }

        Vector3 operator/(const Vector3 &v) const {
            return Vector3{this->x / v.x, this->y / v.y, this->z / v.z};
        }

        Vector3 operator+(float v) const {
            return Vector3{this->x + v, this->y + v, this->z + v};
        }

        Vector3 operator-(float v) const {
            return Vector3{this->x - v, this->y - v, this->z - v};
        }

        Vector3 operator*(float v) const {
            return Vector3{this->x * v, this->y * v, this->z * v};
        }

        Vector3 operator/(float v) const {
            return Vector3{this->x / v, this->y / v, this->z / v};
        }

        Vector3 &operator+=(const Vector3 &v) {
            this->x += v.x;
            this->y += v.y;
            return *this;
        }

        Vector3 &operator-=(const Vector3 &v) {
            this->x -= v.x;
            this->y -= v.y;
            return *this;
        }

        Vector3 &operator*=(const Vector3 &v) {
            this->x *= v.x;
            this->y *= v.y;
            return *this;
        }

        Vector3 &operator/=(const Vector3 &v) {
            this->x /= v.x;
            this->y /= v.y;
            return *this;
        }

        Vector3 &operator+=(float v) {
            this->x += v;
            this->y += v;
            return *this;
        }

        Vector3 &operator-=(float v) {
            this->x -= v;
            this->y -= v;
            return *this;
        }

        Vector3 &operator*=(float v) {
            this->x *= v;
            this->y *= v;
            return *this;
        }

        Vector3 &operator/=(float v) {
            this->x /= v;
            this->y /= v;
            return *this;
        }

        float LengthSqr() const {
            return (x * x) + (y * y) + (z * z);
        }

        float length() const {
            return std::sqrt(LengthSqr());
        }

        Vector3 Normalized() const {
            return (*this) / length();
        }
    };

    using Color = Vector3;

}; // namespace Engine
