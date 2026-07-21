#include "Engine.h"
#include "Mesh.h"
#include "fmod.hpp"
#include "fmod_errors.h"
#include "vector3.h"
#include <iostream>
#include <vector>

#include "Enemy.h"
#include "Player.h"

void PlayAudio(const Engine::Input &engine, FMOD::System &audio, const std::vector<FMOD::Sound *> &sounds) {
    if (engine.GetKeyPressed(SDL_SCANCODE_1)) {
        std::cout << "whistle sound\n";
        audio.playSound(sounds[0], nullptr, false, nullptr);
    }

    if (engine.GetKeyPressed(SDL_SCANCODE_2)) {
        // play another sound
        std::cout << "snare sound\n";
        audio.playSound(sounds[1], nullptr, false, nullptr);
    }

    audio.update();
}

int main(int argc, char *argv[]) {
    // Initalization
    if (const bool init_success = Engine::g_engine.Initialize(); !init_success) {
        return -1;
    }

    std::cout << "Successfully initialized the renderer." << std::endl;

    // mesh / model
    const Engine::Mesh mesh{
        {
         {5, 0},
         {3, -3},
         {1, -3},
         {-1, -2},
         {0, -1},
         {-2, 1},
         {1, 1},
         {5, 0},
         },
        Engine::Color{1.0, 0.0, 0.0}
    };
    const Engine::Model model = std::vector{mesh};

    Engine::Scene       scene;

    PlayerDesc          playerDesc;
    playerDesc.name = "player";
    playerDesc.model = model;
    playerDesc.transform = Engine::Transform{
        Engine::Vector2{(static_cast<float>(Engine::g_engine.GetWindow().window_width) / 2),
                        (static_cast<float>(Engine::g_engine.GetWindow().window_height) / 2)},
        0, 15
    };
    playerDesc.speed = 50.0f;

    Player *player = new Player{playerDesc};

    scene.AddActor(player);

    for (int i = 0; i < 5; i++) {
        EnemyDesc enemy_desc;
        enemy_desc.name = "Enemy" + std::to_string(i + 1);
        enemy_desc.model = model;
        enemy_desc.transform = Engine::Transform{
            Engine::Vector2{
                            Engine::RandomFloat(static_cast<float>(Engine::g_engine.GetWindow().window_width)),
                            Engine::RandomFloat(static_cast<float>(Engine::g_engine.GetWindow().window_height)),
                            },
            90.0f, 10.0f
        };
        enemy_desc.speed = 50.0f;

        Enemy *enemy = new Enemy{enemy_desc};

        scene.AddActor(enemy);
    }

    // Photoshop
    std::vector<Engine::Vector2> points;

    // create audio system
    FMOD::System *audio;
    FMOD::System_Create(&audio);
    void *extra_driver_data = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extra_driver_data);

    std::vector<FMOD::Sound *> sounds;
    FMOD::Sound               *sound = nullptr;

    FMOD_RESULT                result = audio->createSound("sound/mp3/whistle.mp3", FMOD_DEFAULT, nullptr, &sound);
    if (result != FMOD_OK) {
        std::cerr << "createSound failed: " << FMOD_ErrorString(result) << std::endl;
    }

    sounds.push_back(sound);

    result = audio->createSound("sound/wav/snare.wav", FMOD_DEFAULT, nullptr, &sound);
    if (result != FMOD_OK) {
        std::cerr << "createSound failed: " << FMOD_ErrorString(result) << std::endl;
    }

    sounds.push_back(sound);

    // MAIN LOOP
    bool quit = false;
    while (!quit) {
        // UPDATE
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }

            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }
        }

        // Engine
        Engine::g_engine.Update();
        float dt = Engine::g_engine.GetTime().GetDeltaTime();

        scene.Update(dt);

        if (Engine::g_engine.GetInput().GetButtonPressed(Engine::Input::MouseButton::LEFT)) {
            points.push_back(Engine::g_engine.GetInput().GetMousePosition());
        }

        Engine::Vector2 position = Engine::g_engine.GetInput().GetMousePosition();
        if (Engine::g_engine.GetInput().GetButtonDown(Engine::Input::MouseButton::LEFT)) {
            if (points.empty()) {
                points.push_back(Engine::g_engine.GetInput().GetMousePosition());
            } else if ((position - points.back()).length() > 10) {
                points.push_back(Engine::g_engine.GetInput().GetMousePosition());
            }
        }

        // Render
        Engine::g_engine.GetRenderer().SetColor(0.f, 0.f, 0.f, 255.f); // Set draw color to black
        Engine::g_engine.GetRenderer().Clear();                        // Clear the screen

        for (int i = 0; i < static_cast<int>(points.size()) - 1; i++) {
            Engine::g_engine.GetRenderer().SetColor(Engine::RandomFloat(256), Engine::RandomFloat(256),
                                                    Engine::RandomFloat(256), 255);
            Engine::g_engine.GetRenderer().DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        // Actor draw
        scene.Draw(Engine::g_engine.GetRenderer());

        PlayAudio(Engine::g_engine.GetInput(), *audio, sounds);

        Engine::g_engine.GetRenderer().Present(); // Present the rendered content to the screen
    }

    // SHUTDOWN
    Engine::g_engine.Destroy(); // Clean up the renderer and window

    return 0;
}
