#pragma once

#include "Mesh.h"
#include <vector>
namespace Engine {
    class Model {
      public:
        Model() = default;
        Model(const std::vector<Mesh> &mesh) : m_meshes{mesh} {
            CalculateRadius();
        }

        void AddMesh(const Mesh &mesh) {
            m_meshes.push_back(mesh);
            CalculateRadius();
        }

        void SetMeshes(const std::vector<Mesh> &mesh) {
            m_meshes = mesh;
            CalculateRadius();
        }

        const std::vector<Mesh> &GetMeshes() const {
            return m_meshes;
        }

        float GetRadius() const { return m_radius; };
        void CalculateRadius();

      private:
        std::vector<Mesh> m_meshes;
        float m_radius = 0.0f;
    };
} // namespace Engine
