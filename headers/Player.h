//
// Created by brett on 7/20/26.
//

#pragma once
#include "Actor.h"

struct PlayerDesc : public Engine::Actor::ActorDesc {
    float speed;
};

class Player : public Engine::Actor {
  public:
    Player() = default;
    Player(const PlayerDesc &desc) : Actor{desc}, m_speed {desc.speed} {};
    Player(const float speed, const Engine::Transform &transform) : Actor{transform}, m_speed{speed} {};
    Player(const float speed, const Engine::Transform &transform, const Engine::Model &model)
        : Actor{transform, model}, m_speed{speed} {};

    void Update(float dt) override;

    void Draw(const Engine::Renderer &renderer) const override;

  private:
    int   m_ammo = 0;
    float m_speed = 0.0f;
};
