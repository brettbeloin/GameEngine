#include "Actor.h"
#include "MathUtils.h"
#include "renderer.h"

namespace Engine {
    void Actor::Update(float dt) {
        m_transform.position += (m_velocity * dt);
        m_velocity *= .9;

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
