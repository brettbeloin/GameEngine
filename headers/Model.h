#pragma once

#include "Mesh.h"
#include <vector>
namespace Engine {
    class Model {
      public:
        Model() = default;
        Model(const std::vector<Mesh> &mesh) : m_meshes{mesh} {
        }

        void AddMesh(const Mesh &mesh) {
            m_meshes.push_back(mesh);
        }

        void SetMeshes(const std::vector<Mesh> &mesh) {
            m_meshes = mesh;
        }

        const std::vector<Mesh> &GetMeshes() const {
            return m_meshes;
        }

      private:
        std::vector<Mesh> m_meshes;
    };
} // namespace Engine
