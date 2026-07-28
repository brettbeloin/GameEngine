//
// Created by brett on 7/28/26.
//

#pragma once
#include "Game.h"
#include "Scene.h"

class SpaceGame : public Engine::Game {
  public:
    enum class GameState {
        TTILE,
        START,
        START_LEVEL,
        GAME,
        GAME_OVER,
    };

  public:
    SpaceGame() = default;

    explicit SpaceGame(Engine::Scene *scene) : Game(scene) { }

    bool Initialize() override;
    void Destroy() override;


    void Update(float st) override;
    void Draw(const Engine::Renderer &renderer) override;

  private:
    int       m_score = 0;
    int       m_lives = 0;

    GameState m_state = GameState::TTILE;
};
