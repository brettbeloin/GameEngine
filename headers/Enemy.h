//
// Created by brett on 7/21/26.
//

#pragma once
#include "Actor.h"

struct EnemyDesc : public Engine::Actor::ActorDesc {
    float speed;
};

class Enemy : public Engine::Actor {
    public:
    Enemy() = default;
    Enemy(const EnemyDesc &desc) : Actor{desc}, m_speed {desc.speed} {};
    Enemy(const float speed, const Engine::Transform &transform) : Actor{transform}, m_speed{speed} {};
    Enemy(const float speed, const Engine::Transform &transform, const Engine::Model &model)
        : Actor{transform, model}, m_speed{speed} {};

    void Update(float dt) override;

    void OnCollison(Actor *other) override;

    void Draw(const Engine::Renderer &renderer) const override;

    private:
    int   m_ammo = 0;
    float m_speed = 0.0f;
};

