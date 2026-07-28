//
// Created by brett on 7/21/26.
//

#pragma once
#include "Actor.h"

struct BulletDesc : public Engine::Actor::ActorDesc {
    float speed;
};

class Bullet : public Engine::Actor {
  public:
    Bullet() = default;

    explicit Bullet(const BulletDesc &desc) : Actor{desc}, m_speed{desc.speed} {};

    explicit Bullet(const float speed, const Engine::Transform &transform) : Actor{transform}, m_speed{speed} {};

    explicit Bullet(const float speed, const Engine::Transform &transform, const Engine::Model &model)
        : Actor{transform, model}, m_speed{speed} {};

    void Update(float dt) override;

    void OnCollison(Actor *other) override;

  private:
    float m_speed = 0.0f;
};
