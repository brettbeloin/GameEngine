#include "Bullet.h"
#include "Actor.h"
#include "Engine.h"
#include "MathUtils.h"
#include "vector2.h"
#include <iostream>

void Bullet::Update(const float dt) {
    Engine::Vector2 forword{1.0f, 0.0f};
    Engine::Vector2 velocity = forword.Rotate(m_transform.rotation * Engine::DegToRad) * m_speed;

    SetVelocity(velocity);

    Engine::Actor::Update(dt);
}

void Bullet::OnCollison(Actor *other) {
    if (other->GetTag() == "PlayerBullet") {
        SetDestroyed();
        other->SetDestroyed();
    }
}
