//
// Created by brett on 7/28/26.
//

#pragma once
#include "Engine.h"
#include "Font.h"
#include "Game.h"
#include "Scene.h"
#include "Text.h"
#include <string>

class SpaceGame : public Engine::Game {
  public:
    enum class GameState {
        TTILE,
        START_GAME,
        START_LEVEL,
        GAME,
        GAME_OVER,
    };

  public:
    static SpaceGame &GetSpaceGame() {
        static SpaceGame SpaceGame;
        return SpaceGame;
    }

    explicit SpaceGame(Engine::Scene *scene) : Game(scene) {
    }

    bool Initialize() override;
    void Destroy() override;

    void Update(float st) override;
    void Draw(const Engine::Renderer &renderer) override;

    void OnPlayerDead();

    int  GetPoints() {
        return m_score;
    }

    void AddPoints(int points) {
        m_score += points;
    }

    int GetLives() {
        return m_lives;
    }

    float GetFontSize() {
        return m_fontSize;
    }

    void SetFontsize(float size) {
        m_fontSize = size;
    }

    Engine::Font *GetFont() {
        return m_Font;
    }

    Engine::Text *GetText() {
        return m_Text;
    }

  private:
    SpaceGame() = default;
    void SpawnPlayer();
    void SpawnEnemy();

  private:
    int           m_score = 0;
    int           m_lives = 0;

    float         m_fontSize = 0.0f;
    float         m_spawnTime = 5.0f;

    float         m_stateTime = 0.0f;

    GameState     m_state = GameState::TTILE;

    Engine::Font *m_Font = nullptr;
    Engine::Text *m_Text = nullptr;
};
