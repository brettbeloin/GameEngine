//
// Created by brett on 7/21/26.
//

#include "Enemy.h"
#include "Engine.h"
#include "MathUtils.h"
#include "Player.h"
#include "SpaceGame.h"

void Enemy::Update(const float dt) {
    Player *player = m_scene->GetActorByName<Player>("Player");

    if (player) {
        const Engine::Vector2 direction = player->GetTransform().position - m_transform.position;
        float                 rotation = direction.Angle();

        SetRotation(rotation * Engine::RadToDeg);
        Engine::Vector2 fowrard{1, 0}; // ->
        fowrard = fowrard.Rotate(m_transform.rotation * Engine::DegToRad);

        AddVelocity(fowrard * m_speed);
    }

    // partical system
    Engine::Particle particle;
    particle.position = m_transform.position;
    particle.color = {0.0f, 1.0f, 0.0f};
    particle.lifespan = Engine::RandomFloat(0.5f, 1.5f);
    particle.velocity = {Engine::RandomFloat(-200.0f, 200.0f), Engine::RandomFloat(-200.0f, 200.0f)};
    Engine::Engine::GetEngine().GetPS().AddParticle(particle);

    Actor::Update(dt);
}

void Enemy::OnCollison(Actor *other) {

    if (other->GetTag() == "PlayerBullet") {
        SetDestroyed();
        other->SetDestroyed();

        Engine::Engine::GetEngine().GetAudio().PlaySound("snare");

        ((SpaceGame *)m_scene->GetGame())->AddPoints(100);

        for (int i = 0; i < 100; i++) {
            Engine::Particle particle;
            particle.position = m_transform.position;
            particle.color = {0.0f, 0.0f, 1.0f};
            particle.lifespan = Engine::RandomFloat(0.5f, 2.0f);
            particle.velocity = {Engine::RandomFloat(-600.0f, 600.0f), Engine::RandomFloat(-600.0f, 600.0f)};

            Engine::Engine::GetEngine().GetPS().AddParticle(particle);
        }
    }
}
