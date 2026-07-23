//
// Created by brett on 7/21/26.
//

#include "Enemy.h"
#include "Engine.h"
#include "Player.h"

void Enemy::Update(const float dt) {
    Player *player = m_scene->GetActorByName<Player>("Player");
    if (player) {
        const Engine::Vector2 direction = player->GetTransform().position - m_transform.position;
        float                 rotation = direction.Angle();

        SetRotation(m_transform.rotation + rotation * dt);
        Engine::Vector2 fowrard{1, 0}; // ->
        fowrard = fowrard.Rotate(m_transform.rotation * Engine::DegToRad);

        AddVelocity(fowrard * dt);
    }

    // float thrust = 0.0f;
    //
    // float rotation = 0.0f;
    //
    //     Engine::Vector2
    //
    // const Engine::Vector2 velocity = fowrard.Rotate(m_transform.rotation * Engine::DegToRad) * thrust;
    //
    // AddVelocity(velocity * dt);

    Actor::Update(dt);
}

void Enemy::Draw(const Engine::Renderer &renderer) const {
    Actor::Draw(renderer);
}
