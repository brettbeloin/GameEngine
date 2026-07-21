//
// Created by brett on 7/21/26.
//

#include "Enemy.h"
#include "Engine.h"
#include "renderer.h"

void Enemy::Update(const float dt) {
    float thrust = 0.0f;

    float rotation = 0.0f;

    SetRotation(m_transform.rotation + rotation * dt);

    const Engine::Vector2 fowrard{1, 0}; // ->
    const Engine::Vector2 velocity = fowrard.Rotate(m_transform.rotation * Engine::DegToRad) * thrust;

    AddVelocity(velocity * dt);

    Actor::Update(dt);
}

void Enemy::Draw(const Engine::Renderer &renderer) const {
    Actor::Draw(renderer);
}

