#pragma once

#include "vector2.h"
#include "vector3.h"
#include <vector>
namespace Engine {
    class Mesh {
      public:
        Mesh() = default;
        Mesh(std::vector<Vector2> points, const Color &color) : m_points{points}, m_color{color} {};

        const std::vector<Vector2>& GetPoints() const { return m_points; }

        void SetPoints(const std::vector<Vector2> &points) {
            m_points = points;
        }

        const Color &GetColor() const {
            return m_color;
        };

        void SetColor(const std::vector<Vector2> &color) {
            m_points = color;
        }

      private:
        std::vector<Vector2> m_points;
        Color                m_color = {1.0f, 1.0f, 1.0f};
    };
} // namespace Engine
