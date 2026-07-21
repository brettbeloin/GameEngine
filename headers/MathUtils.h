#pragma once

namespace Engine {
    constexpr float         Pi = 3.14159265358979323846264338327950288419716939937510f;
    constexpr float         TwoPi = Pi * 2;
    constexpr float         HalfPi = Pi / 2;

    constexpr float         RadToDeg = 180.f / Pi;
    constexpr float         DegToRad = Pi / 180.f;

    template <typename T> T Wrap(T min, T max, T value) {
        if (value > max) {
            value = min;
        }
        if (value < min) {
            value = max;
        }

        return value;
    }

    template <typename T> T Min(T a, T b) {
        return (a < b) ? a : b;
    }

    template <typename T> T Max(T a, T b) {
        return (a > b) ? a : b;
    }

    template <typename T> T Clamp(T min, T max, T value) {
        if (value > max) {
            value = max;
        }
        if (value < min) {
            value = min;
        }

        return value;
    }

} // namespace Engine
