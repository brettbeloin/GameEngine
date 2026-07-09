#include "Engine.h"
#include "random.h"
#include "vector2.h"
#include <vector>

#include <iostream>

int main(int argc, char *argv[]) {
    Engine::Renderer             renderer;
    constexpr Engine::Window     window = {"Game Engine", 1'000, 1'000}; // Set the window width and height

    Engine::Time                 time;

    Engine::Input                input;

    std::vector<Engine::Vector2> points;
    // Engine::Vector2 pos{(static_cast<float>(window.window_width) / 2), (static_cast<float>(window.window_height) /
    // 2)};

    if (const bool initSuccess = renderer.Initialize(window); !initSuccess) {
        std::cerr << "Failed to initialize the renderer." << std::endl;
        return -1;
    }

    std::cout << "Successfully initialized the renderer." << std::endl;
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

        // float           speed = 100.f;
        // Engine::Vector2 volocity{0.0f, 0.0f};

        // if (input.GetKeyDown(SDL_SCANCODE_A)) {
        //     volocity.x += 1 - speed;
        // }
        //
        // if (input.GetKeyDown(SDL_SCANCODE_D)) {
        //     volocity.x += 1 + speed;
        // }
        // if (input.GetKeyDown(SDL_SCANCODE_W)) {
        //     volocity.y += 1 - speed;
        // }
        // if (input.GetKeyDown(SDL_SCANCODE_S)) {
        //     volocity.y += 1 + speed;
        // }

        // pos += (volocity * time.GetDeltaTime());

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
            }

            if ((position - points.back()).length() > 10) {
                points.push_back(input.GetMousePosition());
            }
        }

        for (int i = 0; i < static_cast<int>(points.size()) - 1; i++) {
            // TODO: Set color or random color.
            // TODO: Call Renderer DrawLine with the std::vector [i] and [i + 1]
            renderer.SetColor(Engine::RandomFloat(256), Engine::RandomFloat(256), Engine::RandomFloat(256), 255);
            renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        // for (int i = 0; i < static_cast<int>(points.size()) - 1; i++) {
        //     renderer.SetColor(Engine::RandomFloat(256), Engine::RandomFloat(256), Engine::RandomFloat(256), 255);
        //     renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        // }

        // renderer.SetColor(255.0f, 0.0f, 0.0f, 255);
        // renderer.DrawFillRect(pos.x - 20, pos.y - 20, 40, 40);

        renderer.Present(); // Present the rendered content to the
                            // screen
    }
    // SHUTDOWN

    renderer.Destroy(); // Clean up the renderer and window

    return 0;
}
