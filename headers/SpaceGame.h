//
// Created by brett on 7/28/26.
//

#pragma once
#include "Engine.h"
#include "Game.h"
#include "Scene.h"

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
    void Draw(Engine::Renderer &renderer);

    void OnPlayerDead();

    int  GetPoints() const {
        return m_score;
    }

    void AddPoints(int points) {
        m_score += points;
    }

    int GetLives() const {
        return m_lives;
    }

    float GetFontSize() const {
        return m_fontSize;
    }

    void SetFontsize(float size) {
        m_fontSize = size;
    }

    Engine::Font *GetFont() const {
        return m_TitleFont;
    }

    Engine::Text *GetText() const {
        return m_TitleText;
    }

    Engine::Font *GetGameFont() const {
        return m_GameFont;
    }
    Engine::Text *GetGameText() const {
        return m_GameText;
    }
    Engine::Font *GetUIFont() const {
        return m_UIFont;
    }
    Engine::Text *GetUIText() const {
        return m_UIText;
    }

    void SetGameFont(Engine::Font *font) {
        m_GameFont = font;
    }
    void SetGameText(Engine::Text *text) {
        m_GameText = text;
    }
    void SetUIFont(Engine::Font *font) {
        m_UIFont = font;
    }
    void SetUIText(Engine::Text *text) {
        m_UIText = text;
    }

  private:
    SpaceGame() = default;
    void SpawnPlayer();
    void SpawnEnemy();

  private:
    int                 m_score = 0;
    int                 m_lives = 3;
    int                 m_spawnCount = 0;

    float               m_fontSize = 0.0f;
    float               m_spawnTimer = 0.0f;
    float               m_spawnTime = 0.0f;

    float               m_stateTime = 0.0f;

    GameState           m_state = GameState::TTILE;

    class Engine::Font *m_TitleFont = nullptr;
    class Engine::Text *m_TitleText = nullptr;

    class Engine::Font *m_GameFont = nullptr;
    class Engine::Text *m_GameText = nullptr;

    class Engine::Font *m_UIFont = nullptr;
    class Engine::Text *m_UIText = nullptr;
};
