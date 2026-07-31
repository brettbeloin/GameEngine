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
                                               SpaceGame::GetSpaceGame().GetLives(),
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
    Game::Destroy();
}

void SpaceGame::Update(float st) {
    switch (m_state) {
    case GameState::TTILE:
        if (Engine::Engine::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
            m_state = GameState::START_GAME;
        }

        break;
    case GameState::START_GAME:
        m_score = 0;
        m_lives = 4;

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
        InsertScore();
        Database::Database::GetDatabase().Update(m_score);

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
    case GameState::GAME:
        m_UIText->Create(Engine::Engine::GetEngine().GetRenderer(),
                         "Score: " + std::to_string(m_score) + " Lives: " + std::to_string(m_lives),
                         Engine::Color{1.0f, 1.0f, 1.0f});
        m_UIText->Draw(renderer, 40.0f, 40.0f);
        break;
    case GameState::GAME_OVER:
        m_TitleText->Create(renderer, "GAME OVER", {1.0f, 1.0f, 1.0f});
        m_TitleText->Draw(renderer, 115, 250);

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

    m_scene->AddActor(player);
}

void SpaceGame::SpawnEnemy() {
    for (int i = 0; i < 5; i++) {
        EnemyDesc enemy_desc;
        enemy_desc.name = "Enemy";
        enemy_desc.model = Assets::enemy_model;
        enemy_desc.transform = Engine::Transform{
            Engine::Vector2{
                            Engine::RandomFloat(static_cast<float>(Engine::Engine::GetEngine().GetWindow().window_width)),
                            Engine::RandomFloat(static_cast<float>(Engine::Engine::GetEngine().GetWindow().window_height)),
                            },
            90.0f, 10.0f
        };
        enemy_desc.damping = 10.0f;
        enemy_desc.speed = Engine::RandomFloat(200.0f, 500.0f);

        Enemy *enemy = new Enemy{enemy_desc};

        m_scene->AddActor(enemy);
    }
}

void SpaceGame::OnPlayerDead() {
    m_lives--;
    m_state = (m_lives == 0) ? GameState::GAME_OVER : GameState::START_LEVEL;
}
