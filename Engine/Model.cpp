//
// Created by brett on 7/27/26.
//
#include "Model.h"
#include "pch.h"

namespace Engine {
    void Model::CalculateRadius() {
        m_radius = 0.0f;

        for (const auto& mesh : m_meshes) {
            // get mesh raduis
            float radius = mesh.GetRadius();

            // of radius is larger that current radius, radius is new radius
            if (radius > 0.0f) {
                m_radius = radius;
            }
        }
    }
}


