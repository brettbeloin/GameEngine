#include "Engine.h"
#include "SpaceGame.h"

int main(int argc, char *argv[]) {
    // Initialization
    if (int init_success = Engine::Engine::GetEngine().Initialize(); !init_success) {
        return -1;
    }

    SpaceGame::GetSpaceGame().Initialize();

    bool quit = false;
    while (!quit) {
        // UPDATE
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT ||
                (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE)) {
                quit = true;
            }
        }

        // Engine
        Engine::Engine::GetEngine().Update();
        float dt = Engine::Engine::GetEngine().GetTime().GetDeltaTime();

        SpaceGame::GetSpaceGame().Update(dt);

        // Render
        Engine::Engine::GetEngine().GetRenderer().SetColor(0.f, 0.f, 0.f, 255.f); // Set draw color to black
        Engine::Engine::GetEngine().GetRenderer().Clear();                        // Clear the screen

        // Actor draw
        SpaceGame::GetSpaceGame().Draw(Engine::Engine::GetEngine().GetRenderer());

        Engine::Engine::GetEngine().GetPS().Draw(Engine::Engine::GetEngine().GetRenderer());

        // MAIN LOOP
        Engine::Engine::GetEngine().GetRenderer().Present(); // Present the rendered content to the screen
    }

    // SHUTDOWN

    Engine::Engine::GetEngine().Destroy(); // Clean up the renderer and window

    return 0;
}
