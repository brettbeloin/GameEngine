//
// Created by brett on 7/28/26.
//

#include "Game.h"
#include "pch.h"

namespace Engine {
    void Game::Update(float st) {
        m_scene->Update(st);
    }
    void Game::Draw(const Renderer& renderer) {
        m_scene->Draw(renderer);
    }
}
