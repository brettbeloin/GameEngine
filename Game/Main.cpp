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
    Database::AddParams params{2, 67, "Test Player", "Player"};
    Database::Database::GetDatabase().ToJSON(params);

    std::string player = "INSERT INTO PLAYER (id, player_name, player_data) VALUES (?, ?,?)";
    Database::Database::GetDatabase().InsertPlayer(player, params);

    std::string score = "INSERT INTO HIGH_SCORE (player_name, score) VALUES (?,?)";

    Database::Database::GetDatabase().InsertScore(score, params);
}

int main(int argc, char *argv[]) {
    bool init_success;

    // Initialization
    if (init_success = Engine::Engine::GetEngine().Initialize(); !init_success) {
        return -1;
    }
    std::cout << "Successfully initialized the renderer." << std::endl;

    // create audio system
    Engine::Engine::GetEngine().GetAudio().AddSound("sound", "Assests/sound/wav/bass.wav");

    SpaceGame game;
    game.Initialize();

    // Text();
    Engine::Font *font = new Engine::Font();
    font->Load("Assests/Fonts/8bitOperatorPlus8-Regular.ttf", 20);

    Engine::Text *text = new Engine::Text(font);
    text->Create(Engine::Engine::GetEngine().GetRenderer(), "Hello World", Engine::Color{1.0f, 1.0f, 1.0f});

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

    // Photoshop
    std::vector<Engine::Vector2> points;

    // MAIN LOOP
    bool quit = false;
    while (!quit) {
        // UPDATE
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT ||
                (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE)) {
                quit = true;
                // insertDummyData();
            }
        }

        // Engine
        Engine::Engine::GetEngine().Update();
        float dt = Engine::Engine::GetEngine().GetTime().GetDeltaTime();

        scene.Update(dt);

        if (Engine::Engine::GetEngine().GetInput().GetButtonPressed(Engine::Input::MouseButton::LEFT)) {
            points.push_back(Engine::Engine::GetEngine().GetInput().GetMousePosition());
        }

        Engine::Vector2 position = Engine::Engine::GetEngine().GetInput().GetMousePosition();
        if (Engine::Engine::GetEngine().GetInput().GetButtonDown(Engine::Input::MouseButton::LEFT)) {
            if (points.empty()) {
                points.push_back(Engine::Engine::GetEngine().GetInput().GetMousePosition());
            } else if ((position - points.back()).length() > 10) {
                points.push_back(Engine::Engine::GetEngine().GetInput().GetMousePosition());
            }
        }

        // Render
        Engine::Engine::GetEngine().GetRenderer().SetColor(0.f, 0.f, 0.f, 255.f); // Set draw color to black
        Engine::Engine::GetEngine().GetRenderer().Clear();                        // Clear the screen

        for (int i = 0; i < static_cast<int>(points.size()) - 1; i++) {
            Engine::Engine::GetEngine().GetRenderer().SetColor(Engine::RandomFloat(256), Engine::RandomFloat(256),
                                                               Engine::RandomFloat(256), 255);
            Engine::Engine::GetEngine().GetRenderer().DrawLine(points[i].x, points[i].y, points[i + 1].x,
                                                               points[i + 1].y);
        }

        // Actor draw
        scene.Draw(Engine::Engine::GetEngine().GetRenderer());
        text->Draw(Engine::Engine::GetEngine().GetRenderer(), 40.0f, 40.0f);

        Engine::Engine::GetEngine().GetRenderer().Present(); // Present the rendered content to the screen
    }

    // SHUTDOWN
    Engine::Engine::GetEngine().Destroy(); // Clean up the renderer and window

    return 0;
}
