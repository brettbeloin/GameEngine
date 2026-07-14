#include "Actor.h"
#include "MathUtils.h"
#include "pch.h"
#include "renderer.h"

namespace Engine {
    void Actor::Update(float dt) {
        m_transform.position += (m_velocity * dt);
        m_velocity *= .9;

        m_transform.position.x = Engine::Clamp(0.f, 500.f, m_transform.position.x);
        m_transform.position.y = Engine::Wrap(0.f, 500.f, m_transform.position.y);
    }

    void Actor::Draw(const Renderer &renderer) const {
        renderer.SetColor(m_model.GetColor().r, m_model.GetColor().g, m_model.GetColor().b, 255);

        // renderer.SetColor(static_cast<Uint8>(255), 0.0, 0.0, 255);
        // renderer.DrawPoint(m_transform.position.x, m_transform.position.y);
        renderer.DrawLine(m_transform.position.x - (m_transform.scale * .5f),
                          m_transform.position.y - (m_transform.scale * .5f), m_transform.scale, m_transform.scale);
    }

} // namespace Engine
