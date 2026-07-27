//
// Created by brett on 7/27/26.
//
#include "Mesh.h"

namespace Engine {
    float Mesh::GetRadius() const {
        float radius = 0.0f;

        for (const auto& point : m_points) {
            float length = point.length();
            if (length > 0.0f) {
                radius = length;
            }
        }

        return radius;
    }
}
