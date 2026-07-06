#pragma once

namespace Engine {
class Vector2 {
public:
  Vector2() = default;
  Vector2(float x, float y) : x{x}, y{y} {};
  Vector2(float v) : x{v}, y{v} {};

  float x, y;
};
}; // namespace Engine
