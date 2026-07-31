//
// Created by brett on 7/20/26.
//
#include "Player.h"
#include "Assets.h"
#include "Bullet.h"
#include "Engine.h"
#include "SpaceGame.h"
#include <iostream>

void Player::Update(const float dt) {
    if (m_invulnerableTime > 0.0f) {
        m_invulnerableTime -= dt;
    }

    // Movement

    float thrust = 0.0f;
    if (Engine::Engine::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W) ||
        Engine::Engine::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_UP)) {
        thrust = m_speed;
    }

    if (Engine::Engine::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S) ||
        Engine::Engine::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_DOWN)) {
        thrust = -m_speed;
    }

    float rotation = 0.0f;

    if (Engine::Engine::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A) ||
        Engine::Engine::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_LEFT)) {
        rotation = -180.0f;
    }

    if (Engine::Engine::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D) ||
        Engine::Engine::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_RIGHT)) {
        rotation = +180.0f;
    }

    SetRotation(m_transform.rotation + (rotation * dt));

    const Engine::Vector2 fowrard{1, 0}; // ->
    const Engine::Vector2 velocity = fowrard.Rotate(m_transform.rotation * Engine::DegToRad) * thrust;

    AddVelocity(velocity);

    // partical system
    Engine::Particle particle;
    particle.position = m_transform.position;
    particle.color = {1.0f, 1.0f, 1.0f};
    particle.lifespan = Engine::RandomFloat(0.5f, 1.5f);
    particle.velocity = {Engine::RandomFloat(-200.0f, 200.0f), Engine::RandomFloat(-200.0f, 200.0f)};

    Engine::Engine::GetEngine().GetPS().AddParticle(particle);

    // fire
    if (Engine::Engine::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
        BulletDesc bullet_desc;
        bullet_desc.name = "Bullet";
        bullet_desc.tag = "PlayerBullet";
        bullet_desc.model = Assets::bullet_model;
        bullet_desc.transform = m_transform;
        // bullet_desc.damping = 10.0f;
        bullet_desc.speed = 400.0f;
        bullet_desc.lifeSpawn = 1.0f;

        Bullet *bullet = new Bullet{bullet_desc};
        m_scene->AddActor(bullet);
    }

    Actor::Update(dt);
}

void Player::OnCollison(Actor *other) {
    if (other->GetName() == "Enemy" && !IsInvulnerable()) {
        SetDestroyed();

        ((SpaceGame *)m_scene->GetGame())->OnPlayerHit();
    }
}
