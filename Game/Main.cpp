#include "Database.h"
#include "Engine.h"
#include "fmod.hpp"
#include <iostream>
#include <string>
#include <vector>

#include "Enemy.h"
#include "Player.h"

#include "Assets.h"

void Text() {
    // get current working directory
    std::cout << "Directory Operations:\n";
    std::cout << "Working directory: " << Engine::GetWorkingDirectory() << "\n";

    // set working directory (current working directory + "Assets")
    std::cout << "Setting directory to 'Assets'...\n";
    Engine::SetWorkingDirectory("Assets");
    std::cout << "New directory: " << Engine::GetWorkingDirectory() << "\n\n";

    // get filenames in the working directory
    std::cout << "Files in Directory:\n";
    auto filenames = Engine::GetFilesInDirectory(Engine::GetWorkingDirectory());
    for (const auto &filename : filenames) {
        std::cout << filename << "\n";
    }
    std::cout << "\n";

    // get filename info
    if (!filenames.empty()) {
        // get filename
        std::string str = Engine::GetFilename(filenames[0]);
        std::cout << "Filename: " << str << "\n";

        // get extension
        str = Engine::GetFileExtension(filenames[0]);
        std::cout << "Extension: " << str << "\n";

        // get filename no extension
        str = Engine::GetFilenameNoExtension(filenames[0]);
        std::cout << "Filename No Extension: " << str << "\n\n";
    }

    // read and display text file
    std::cout << "Text File Reading:\n";
    std::string str;
    if (Engine::ReadTextFile("test.txt", str)) {
        std::cout << str << "\n";
    }

    // write to text file
    std::cout << "Text File Writing:\n";
    Engine::WriteTextFile("test.txt", "Hello, World!", true);
    if (Engine::ReadTextFile("test.txt", str)) {
        std::cout << str << "\n";
    }
}

void PlayAudio() {
    if (Engine::Engine::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_1)) {
        Engine::Engine::GetEngine().GetAudio().PlaySound("sound");
    }
}

void insertDummyData() {
    Database::AddParams params;

    std::string         player = "INSERT INTO TEST_PLAYER (player_name, player_data) VALUES (?,?)";
    params.name = "Test Player";

    Database::Database::GetDatabase().AddNewRecord(player, params);

    std::string score = "INSERT INTO TEST_SCORE (player_name, score) VALUES (?,?)";
    params.score = 67;

    Database::Database::GetDatabase().AddNewRecord(score, params);
}

int main(int argc, char *argv[]) {

    bool init_success;

    // Initialization
    if (init_success = Engine::Engine::GetEngine().Initialize(); !init_success) {
        return -1;
    }
    std::cout << "Successfully initialized the renderer." << std::endl;

    if (init_success = Database::Database::GetDatabase().Init(); !init_success) {
        return -1;
    }

    // create audio system
    Engine::Engine::GetEngine().GetAudio().AddSound("sound", "Assests/sound/wav/bass.wav");

    // Text();

    Engine::Scene scene;

    PlayerDesc    playerDesc;
    playerDesc.name = "player";
    playerDesc.model = Assets::player_model;
    playerDesc.transform = Engine::Transform{
        Engine::Vector2{(static_cast<float>(Engine::Engine::GetEngine().GetWindow().window_width) / 2),
                        (static_cast<float>(Engine::Engine::GetEngine().GetWindow().window_height) / 2)},
        0, 15
    };
    playerDesc.speed = 200.0f;

    Player *player = new Player{playerDesc};

    scene.AddActor(player);

    for (int i = 0; i < 5; i++) {
        EnemyDesc enemy_desc;
        enemy_desc.name = "Enemy" + std::to_string(i + 1);
        enemy_desc.model = Assets::player_model;
        enemy_desc.transform = Engine::Transform{
            Engine::Vector2{
                            Engine::RandomFloat(static_cast<float>(Engine::Engine::GetEngine().GetWindow().window_width)),
                            Engine::RandomFloat(static_cast<float>(Engine::Engine::GetEngine().GetWindow().window_height)),
                            },
            90.0f, 10.0f
        };
        enemy_desc.speed = 50.0f;

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
                insertDummyData();
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

        PlayAudio();

        Engine::Engine::GetEngine().GetRenderer().Present(); // Present the rendered content to the screen
    }

    // SHUTDOWN
    Database::Database::GetDatabase().Destroy();
    Engine::Engine::GetEngine().Destroy(); // Clean up the renderer and window

    return 0;
}
