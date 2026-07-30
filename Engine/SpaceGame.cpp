//
// Created by brett on 7/28/26.
//

#include "SpaceGame.h"

#include "Assets.h"
#include "Database.h"
#include "Enemy.h"
#include "Engine.h"
#include "Player.h"
#include "renderer.h"
#include <iostream>
#include <string>

std::string GetPlayerData() {
    std::string playerData = Database::Database::GetDatabase().GetSinglePlayer("Player");
    // std::cout << playerData << "\n";

    nlohmann::json j = nlohmann::json::parse(playerData);
    int            score = j["score"];
    int            lives = j["lives"];

    return "Score: " + std::to_string(score) + " lives: " + std::to_string(lives);
}

void DisplayUI() {
}

void InsertPlayer() {
    Database::Database::GetDatabase().ToJSON(Database::AddParams::GetParams());

    Database::Database::GetDatabase().InsertPlayer(Database::AddParams::GetParams());
}

void InsertScore() {

    Database::Database::GetDatabase().InsertScore(Database::AddParams::GetParams());
}

bool SpaceGame::Initialize() {
    Game::Initialize();

    m_scene = new Engine::Scene();
    m_scene->SetGame(this);

    m_Font = new Engine::Font();

    m_Text = new Engine::Text(m_Font);

    Database::AddParams::GetParams().SetParams(1, SpaceGame::GetSpaceGame().GetPoints(),
                                               SpaceGame::GetSpaceGame().GetLives(), "Player", "Player", "");

    return true;
}

void SpaceGame::Destroy() {
    delete m_Font;
    m_Font = nullptr;
    delete m_Text;
    m_Text = nullptr;
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
        m_lives = 3;

        InsertPlayer();

        m_fontSize = 10.0f;
        m_spawnTime = 5.0f;
        m_stateTime = .05f;

        m_state = GameState::START_LEVEL;
        break;
    case GameState::START_LEVEL:
        m_scene->RemoveALLActors();
        SpawnPlayer();

        m_state = GameState::GAME;
        break;
    case GameState::GAME:
        m_spawnTime -= st;

        if (m_spawnTime < 0.0f) {
            m_spawnTime = 5.0f;
            SpawnEnemy();
        }

        break;
    case GameState::GAME_OVER:
        InsertScore();

        m_stateTime -= st;

        if (m_stateTime <= 0) {
        }

        break;
    };

    Game::Update(st);
}

void SpaceGame::Draw(const Engine::Renderer &renderer) {
    switch (m_state) {
    case GameState::TTILE:
        m_fontSize = 50.0f;
        m_Font->Load("Assests/Fonts/8bitOperatorPlus8-Bold.ttf", m_fontSize);
        m_Text->Create(Engine::Engine::GetEngine().GetRenderer(), "MAIN MENU", Engine::Color{1.0f, 1.0f, 1.0f});
        m_Text->Draw(Engine::Engine::GetEngine().GetRenderer(), 40.0f, 40.0f);

        m_Text->Draw(renderer, 40.0f, 40.0f);

        break;
    case GameState::START_GAME:
    case GameState::START_LEVEL:
    case GameState::GAME:
        // SpaceGame::GetSpaceGame().SetFontsize(20);
        // SpaceGame::GetSpaceGame().GetFont()->Load("Assests/Fonts/8bitOperatorPlus8-Regular.ttf",
        //                                           SpaceGame::GetSpaceGame().GetFontSize());
        //
        // SpaceGame::GetSpaceGame().GetText()->Create(Engine::Engine::GetEngine().GetRenderer(),
        //                                             "Score: " + std::to_string(m_score) +
        //                                                 " Lives: " + std::to_string(m_lives),
        //                                             Engine::Color{1.0f, 1.0f, 1.0f});
        //
        // SpaceGame::GetSpaceGame().GetText()->Draw(Engine::Engine::GetEngine().GetRenderer(), 40.0f, 40.0f);
        break;
    case GameState::GAME_OVER:

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
        enemy_desc.speed = Engine::RandomFloat(1000.0f, 2000.0f);

        Enemy *enemy = new Enemy{enemy_desc};

        m_scene->AddActor(enemy);
    }
}

void SpaceGame::OnPlayerDead() {
    m_lives--;
    m_state = (m_lives == 0) ? GameState::GAME_OVER : GameState::START_LEVEL;
}
