#pragma once
#include "Model.h"
#include "Transform.h"

namespace Engine {
    class Actor {
      public:
        Actor() = default;
        Actor(const Transform &transform) : m_transform{transform} {};
        Actor(const Transform &transform, const Mesh &mesh) : m_transform{transform}, m_model{mesh} {};

        void             Update(float dt);

        void             Draw(const class Renderer &renderer) const;

        const Transform &GetTransform() const {
            return m_transform;
        }

        const Engine::Vector2 &GetVelocity() const {
            return m_velocity;
        }

        void SetScale(float scale) {
            m_transform.scale = scale;
        }

        void SetVelocity(const Engine::Vector2 &position) {
            m_velocity = position;
        }

        void SetRotation(float rotation) {
            m_transform.rotation = rotation;
        }

      protected:
        Transform       m_transform;
        Engine::Vector2 m_velocity{0, 0};

        Mesh            m_model;
    };
} // namespace Engine
