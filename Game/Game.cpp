#include "Engine.h"
// #include "Input.h"
#include "random.h"
#include <vector>

#include <iostream>

int main(int argc, char *argv[]) {
    Engine::Renderer             renderer;
    constexpr Engine::Window     window = {"Game Engine", 500, 500}; // Set the window width and height

    float                        xs[30];
    float                        yx[30];

    Engine::Input                input;

    std::vector<Engine::Vector2> v;

    for (int i = 0; i < 30; i++) {
        Engine::Vector2 vec{Engine::RandomFloat(500), Engine::RandomFloat(500)};
        v.push_back(vec);
    }

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

        if (input.GetKeyPressed(SDL_SCANCODE_Q)) {
            std::cout << "Key down\n";
        }

        // RENDERER

        // if (key_state[SDL_SCANCODE_SPACE]) {
        //     std::cout << "space\n";
        // }

        Engine::Vector2 mouse_pos;
        SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);

        renderer.SetColor(0.f, 0.f, 0.f, 255.f); // Set draw color to black

        renderer.Clear();                        // Clear the screen

        for (int i = 0; i < v.size(); i++) {
            v[i] = v[i] + 5;
            renderer.DrawPoint(v[i].x, v[i].y);
        };

        renderer.SetColor(255.0f, 0.0f, 0.0f, 255);
        renderer.DrawFillRect(input.GetMousePosition().x - 20, input.GetMousePosition().y - 20, 40, 40);

        renderer.Present(); // Present the rendered content to the
                            // screen
    }
    // SHUTDOWN

    renderer.Destroy(); // Clean up the renderer and window

    return 0;
}
