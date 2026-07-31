//
// Created by brett on 7/28/26.
//

#include "SpaceGame.h"

#include "Actor.h"
#include "Assets.h"
#include "Audio.h"
#include "Database.h"
#include "Enemy.h"
#include "Engine.h"
#include "Player.h"
#include "random.h"
#include "renderer.h"
// #include <iostream>
#include <string>

namespace {
    constexpr int   kNormalStartHealth = 10;
    constexpr int   kHardStartHealth = 5;
    constexpr int   kDamagePerHit = 1;

    constexpr float kNormalEnemySpeedMin = 80.0f;
    constexpr float kNormalEnemySpeedMax = 180.0f;
    constexpr float kHardEnemySpeedMin = 150.0f;
    constexpr float kHardEnemySpeedMax = 300.0f;
} // namespace

void InsertPlayer() {
    Database::Database::GetDatabase().ToJSON(Database::AddParams::GetParams());

    Database::Database::GetDatabase().InsertPlayer(Database::AddParams::GetParams());
}

void InsertScore() {
    Database::AddParams::GetParams().m_score = SpaceGame::GetSpaceGame().GetPoints();
    Database::Database::GetDatabase().InsertScore(Database::AddParams::GetParams());
}

bool SpaceGame::Initialize() {
    Game::Initialize();

    m_scene = new Engine::Scene();
    m_scene->SetGame(this);
    m_fontSize = 50.0f;

    m_TitleFont = new Engine::Font();
    m_TitleText = new Engine::Text(m_TitleFont);
    m_TitleFont->Load("Assests/Fonts/8bitOperatorPlus8-Bold.ttf", m_fontSize);
    m_TitleText->Create(Engine::Engine::GetEngine().GetRenderer(), "MAIN MENU", Engine::Color{1.0f, 1.0f, 1.0f});

    m_UIFont = new Engine::Font();
    m_UIText = new Engine::Text(m_UIFont);
    m_UIFont->Load("Assests/Fonts/8bitOperatorPlus8-Regular.ttf", 20);

    Database::AddParams::GetParams().SetParams(1, SpaceGame::GetSpaceGame().GetPoints(),
                                               SpaceGame::GetSpaceGame().GetHealth(),
                                               Player::GetPlayer().GetTransform().position.x,
                                               Player::GetPlayer().GetTransform().position.y, "Player", "Player", "");

    Engine::Engine::GetEngine().GetAudio().AddSound("snare", "Assests/sound/wav/snare.wav");

    return true;
}

void SpaceGame::Destroy() {
    delete m_TitleFont;
    m_TitleFont = nullptr;
    delete m_TitleText;
    m_TitleText = nullptr;

    for (Engine::Text *text : m_HighScoreTexts) {
        delete text;
    }
    m_HighScoreTexts.clear();

    Game::Destroy();
}

void SpaceGame::Update(float st) {
    switch (m_state) {
    case GameState::TTILE:
        if (Engine::Engine::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
            m_hardMode = false;
            m_state = GameState::START_GAME;
        } else if (Engine::Engine::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_RETURN)) {
            m_hardMode = true;
            m_state = GameState::START_GAME;
        }

        break;
    case GameState::START_GAME:
        m_score = 0;
        m_health = m_hardMode ? kHardStartHealth : kNormalStartHealth;

        InsertPlayer();

        m_fontSize = 10.0f;
        m_spawnTime = 5.0f;
        m_stateTime = .05f;

        m_state = GameState::START_LEVEL;
        break;
    case GameState::START_LEVEL:
        m_stateTime -= st;
        if (m_stateTime <= 0) {

            m_scene->RemoveALLActors();
            SpawnPlayer();
            m_spawnTime = 5.0f;
            m_spawnTimer = 0.0f;

            m_state = GameState::GAME;
        }

        break;
    case GameState::GAME:
        m_spawnTimer -= st;

        if (m_spawnTimer <= 0.0f) {
            m_spawnTimer = m_spawnTime;
            SpawnEnemy();
            m_spawnCount++;

            if (m_score % 500 == 0) {
                m_spawnTime -= .05;
            }
        }

        break;
    case GameState::GAME_OVER:
        m_stateTime -= st;
        if (m_stateTime <= 0) {
            m_scene->RemoveALLActors();
            m_state = GameState::TTILE;
        }

        break;
    };

    Game::Update(st);
}

void SpaceGame::Draw(Engine::Renderer &renderer) {
    switch (m_state) {
    case GameState::TTILE:
        m_TitleText->Draw(renderer, 115, 250);
        break;
    case GameState::START_GAME:
    case GameState::START_LEVEL:
    case GameState::GAME: {
        std::string uiString = "Score: " + std::to_string(m_score) + " Health: " + std::to_string(m_health);
        if (uiString != m_lastUIString) {
            m_UIText->Create(Engine::Engine::GetEngine().GetRenderer(), uiString, Engine::Color{1.0f, 1.0f, 1.0f});
            m_lastUIString = uiString;
        }
        m_UIText->Draw(renderer, 40.0f, 40.0f);
        break;
    }
    case GameState::GAME_OVER:
        m_TitleText->Create(renderer, "GAME OVER", {1.0f, 1.0f, 1.0f});
        m_TitleText->Draw(renderer, 115, 250);

        for (size_t i = 0; i < m_HighScoreTexts.size(); i++) {
            m_HighScoreTexts[i]->Draw(renderer, 150.0f, 310.0f + static_cast<float>(i) * 25.0f);
        }

        break;
    }

    Game::Draw(renderer);
}

void SpaceGame::SpawnPlayer() {
    PlayerDesc playerDesc;
    playerDesc.name = "Player";
    playerDesc.model = Assets::player_model;
    playerDesc.transform = Engine::Transform{
        Engine::Vector2{(static_cast<float>(Engine::Engine::GetEngine().GetWindow().window_width) / 2),
                        (static_cast<float>(Engine::Engine::GetEngine().GetWindow().window_height) / 2)},
        0, 15
    };
    playerDesc.damping = 1.0f;
    playerDesc.speed = 500.0f;

    Player *player = new Player{playerDesc};
    player->SetInvulnerable(1.5f);

    m_scene->AddActor(player);
}

void SpaceGame::SpawnEnemy() {
    constexpr float kMinSpawnDistance = 150.0f;

    Player         *player = m_scene->GetActorByName<Player>("Player");

    for (int i = 0; i < 5; i++) {
        Engine::Vector2 spawn_pos;
        for (int attempt = 0; attempt < 10; attempt++) {
            spawn_pos = Engine::Vector2{
                Engine::RandomFloat(static_cast<float>(Engine::Engine::GetEngine().GetWindow().window_width)),
                Engine::RandomFloat(static_cast<float>(Engine::Engine::GetEngine().GetWindow().window_height)),
            };

            if (!player || (spawn_pos - player->GetTransform().position).length() >= kMinSpawnDistance) {
                break;
            }
        }

        EnemyDesc enemy_desc;
        enemy_desc.name = "Enemy";
        enemy_desc.model = Assets::enemy_model;
        enemy_desc.transform = Engine::Transform{spawn_pos, 90.0f, 10.0f};
        enemy_desc.damping = 10.0f;
        enemy_desc.speed = m_hardMode ? Engine::RandomFloat(kHardEnemySpeedMin, kHardEnemySpeedMax)
                                       : Engine::RandomFloat(kNormalEnemySpeedMin, kNormalEnemySpeedMax);

        Enemy *enemy = new Enemy{enemy_desc};

        m_scene->AddActor(enemy);
    }
}

void SpaceGame::RefreshHighScores() {
    for (Engine::Text *text : m_HighScoreTexts) {
        delete text;
    }
    m_HighScoreTexts.clear();

    for (const std::string &line : Database::Database::GetDatabase().ReadAllHighScores(5)) {
        Engine::Text *text = new Engine::Text(m_UIFont);
        text->Create(Engine::Engine::GetEngine().GetRenderer(), line, Engine::Color{1.0f, 1.0f, 1.0f});

        m_HighScoreTexts.push_back(text);
    }
}

void SpaceGame::OnPlayerHit() {
    m_health -= kDamagePerHit;

    if (m_health <= 0) {
        m_state = GameState::GAME_OVER;
        m_stateTime = 5.0f;

        InsertScore();
        Database::Database::GetDatabase().Update(m_score);
        RefreshHighScores();
    } else {
        m_state = GameState::START_LEVEL;
        m_stateTime = .05f;
    }
}
