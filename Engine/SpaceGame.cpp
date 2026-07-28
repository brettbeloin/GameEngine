//
// Created by brett on 7/28/26.
//

#include "SpaceGame.h"

#include "Engine.h"
#include "renderer.h"
#include "Player.h"

bool SpaceGame::Initialize() {
    Game::Initialize();

    m_scene = new Engine::Scene();

    return true;
}

void SpaceGame::Destroy() {
    Game::Destroy();
}

void SpaceGame::Update(float st) {
    switch (m_state) {
    case GameState::TTILE:
        if (Engine::Engine::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
        }
        break;
    case GameState::START:

    case GameState::START_LEVEL:
    case GameState::GAME:
        break;
    case GameState::GAME_OVER:
        break;
    };

    Game::Update(st);
}

void SpaceGame::Draw(const Engine::Renderer &renderer) {
    Game::Draw(renderer);
}
