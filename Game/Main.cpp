#include "Database.h"
#include "Engine.h"
#include <iostream>
#include <string>
#include <vector>

#include "Enemy.h"

#include "Assets.h"
#include "Player.h"
#include "SpaceGame.h"
#include "random.h"

/*
 * TODO Make the enemy's rotate and chase the player
 * TODO Fix Enemy from floating to edge of screen
 * TODO Destroy enemies
 */

void insertDummyData() {
    Database::AddParams params{1, 67, "Player", "Player"};
    Database::Database::GetDatabase().ToJSON(params);

    Database::Database::GetDatabase().InsertPlayer(params);

    Database::Database::GetDatabase().InsertScore(params);
    params.name = "foo";
    Database::Database::GetDatabase().InsertScore(params);
}

void getAllDummyData() {
}

int main(int argc, char *argv[]) {
    // Initialization
    if (int init_success = Engine::Engine::GetEngine().Initialize(); !init_success) {
        return -1;
    }
    std::cout << "Successfully initialized the renderer." << std::endl;

    Engine::Font *font = new Engine::Font();
    font->Load("Assests/Fonts/8bitOperatorPlus8-Regular.ttf", 20);

    Engine::Text *text = new Engine::Text(font);
    text->Create(Engine::Engine::GetEngine().GetRenderer(), Database::Database::GetDatabase().GetSingleScore("foo"),
                 Engine::Color{1.0f, 1.0f, 1.0f});

    // Test Getting all data
    // Database::Database::GetDatabase().ReadAllHighScores(5);

    SpaceGame game;
    game.Initialize();

    Engine::Scene scene;

    PlayerDesc    playerDesc;
    playerDesc.name = "player";
    playerDesc.model = Assets::player_model;
    playerDesc.transform = Engine::Transform{
        Engine::Vector2{(static_cast<float>(Engine::Engine::GetEngine().GetWindow().window_width) / 2),
                        (static_cast<float>(Engine::Engine::GetEngine().GetWindow().window_height) / 2)},
        0, 15
    };
    playerDesc.damping = 1.0f;
    playerDesc.speed = 500.0f;

    Player *player = new Player{playerDesc};

    scene.AddActor(player);

    for (int i = 0; i < 5; i++) {
        EnemyDesc enemy_desc;
        enemy_desc.name = "Enemy" + std::to_string(i + 1);
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

        scene.AddActor(enemy);
    }

    bool quit = false;
    while (!quit) {
        // UPDATE
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT ||
                (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE)) {
                quit = true;
                insertDummyData();
            }
        }

        // Engine
        Engine::Engine::GetEngine().Update();
        float dt = Engine::Engine::GetEngine().GetTime().GetDeltaTime();

        scene.Update(dt);

        // Render
        Engine::Engine::GetEngine().GetRenderer().SetColor(0.f, 0.f, 0.f, 255.f); // Set draw color to black
        Engine::Engine::GetEngine().GetRenderer().Clear();                        // Clear the screen

        // Actor draw
        scene.Draw(Engine::Engine::GetEngine().GetRenderer());

        text->Draw(Engine::Engine::GetEngine().GetRenderer(), 40.0f, 40.0f);

        // MAIN LOOP
        Engine::Engine::GetEngine().GetRenderer().Present(); // Present the rendered content to the screen
    }

    // SHUTDOWN

    delete font;
    font = nullptr;
    delete text;
    text = nullptr;

    Engine::Engine::GetEngine().Destroy(); // Clean up the renderer and window

    return 0;
}
