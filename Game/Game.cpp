#include "Engine.h"
#include "Mesh.h"
#include "vector2.h"
#include "vector3.h"
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
    Engine::Renderer     renderer;
    const Engine::Window window = {"Game Engine", 500, 500}; // Set the window width and height

    Engine::Mesh         mesh{
        std::vector<Engine::Vector2>{{-3.0f, 3.0f}, {3.0f, 3.0f}, {0.0f, 0.0f}},
        Engine::Vector3{          255,            0,            0}
    };

    Engine::Actor player{
        Engine::Transform{Engine::Vector2{(static_cast<float>(window.window_width) / 2),
                                          (static_cast<float>(window.window_height) / 2)},
                          0, 50},
        {mesh}
    };

    Engine::Time                 time;

    Engine::Input                input;

    std::vector<Engine::Vector2> points;

    float                        speed = 50.f;
    Engine::Vector2              volocity = 0;

    if (const bool initSuccess = renderer.Initialize(window); !initSuccess) {
        std::cerr << "Failed to initialize the renderer." << std::endl;
        return -1;
    }

    // std::cout << "Successfully initialized the renderer." << std::endl;
    input.Initialize();

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
        input.Update();
        time.Tick();

        Engine::Vector2 force{.0f, 0.f};
        if (input.GetKeyDown(SDL_SCANCODE_A) || input.GetKeyDown(SDL_SCANCODE_LEFT)) {
            force.x += 1 - speed;
        }

        if (input.GetKeyDown(SDL_SCANCODE_D) || input.GetKeyDown(SDL_SCANCODE_RIGHT)) {
            force.x += 1 + speed;
        }
        if (input.GetKeyDown(SDL_SCANCODE_W) || input.GetKeyDown(SDL_SCANCODE_UP)) {
            force.y += 1 - speed;
        }
        if (input.GetKeyDown(SDL_SCANCODE_S) || input.GetKeyDown(SDL_SCANCODE_DOWN)) {
            force.y += 1 + speed;
        }

        player.SetVelocity(player.GetVelocity() + (force * time.GetDeltaTime()));
        player.Update(time.GetDeltaTime());

        // RENDERER

        Engine::Vector2 mouse_pos;
        SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);

        renderer.SetColor(0.f, 0.f, 0.f, 255.f); // Set draw color to black

        renderer.Clear();                        // Clear the screen

        // step one
        if (input.GetButtonPressed(Engine::Input::MouseButton::LEFT)) {
            // TODO: Add mouse position to std::vector.
            points.push_back(input.GetMousePosition());
        }

        // step two
        Engine::Vector2 position = input.GetMousePosition();
        if (input.GetButtonDown(Engine::Input::MouseButton::LEFT)) {
            if (points.empty()) {
                points.push_back(input.GetMousePosition());
            } else if ((position - points.back()).length() > 10) {
                points.push_back(input.GetMousePosition());
            }
        }

        for (int i = 0; i < static_cast<int>(points.size()) - 1; i++) {
            // TODO: Set color or random color.
            // TODO: Call Renderer DrawLine with the std::vector [i] and [i + 1]
            renderer.SetColor(Engine::RandomFloat(256), Engine::RandomFloat(256), Engine::RandomFloat(256), 255);
            renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        player.Draw(renderer);

        renderer.Present(); // Present the rendered content to the
                            // screen
    }
    // SHUTDOWN

    renderer.Destroy(); // Clean up the renderer and window

    return 0;
}
