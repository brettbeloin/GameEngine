//
// Created by brett on 7/20/26.
//
#include "Player.h"
#include "Engine.h"
#include "renderer.h"

void Player::Update(const float dt) {
float thrust = 0.0f;

    if (Engine::Engine::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W) ||
       Engine::Engine::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_UP)) {
        thrust = m_speed;
        }

    if  (Engine::Engine::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S) ||
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
        rotation = 180.0f;
    }

    SetRotation(m_transform.rotation + rotation * dt);

    const Engine::Vector2 fowrard{1, 0}; // ->
    const Engine::Vector2 velocity = fowrard.Rotate(m_transform.rotation * Engine::DegToRad) * thrust;

    AddVelocity(velocity * dt);

    Actor::Update(dt);
}

void Player::Draw(const Engine::Renderer &renderer) const {
    Actor::Draw(renderer);
}

void Player::OnCollison(Actor *other) {
    if (other->GetName() == "Enemy") {
        SetDestroyed();
    }
}
