#include "Actor.h"
#include "MathUtils.h"
#include "pch.h"
#include "renderer.h"

namespace Engine {
    void Actor::Update(float dt) {
        // lifeSpan
        if (GetLifeSpawn() > 0) {
            SetLifeSpawn(GetLifeSpawn() - dt);
            m_destroyed = (GetLifeSpawn() <= 0.0f);
        }

        // physics
        m_transform.position += (m_velocity * dt);
        m_velocity *= 1.0f / (1.0f) + GetDamping() * dt;

        m_transform.position.x = Clamp(0.f, 500.f, m_transform.position.x);
        m_transform.position.y = Wrap(0.f, 500.f, m_transform.position.y);
    }

    void Actor::Draw(const Renderer &renderer) const {
        renderer.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
        renderer.DrawModel(m_model, m_transform);
    }

    float Actor::GetRadius() const {
        return m_model.GetRadius() * m_transform.scale * .9f;
    }
} // namespace Engine
