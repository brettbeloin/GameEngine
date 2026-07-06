#include "Engine.h"
#include "random.h"
#include <vector>
// #include "SDL3/SDL.h"

#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[]) {
  Engine::Renderer renderer;
  constexpr Engine::Window window = {"Game Engine", 500,
                                     500}; // Set the window width and height

  float xs[30];
  float yx[30];

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

  bool quit = false;
  while (!quit) {

    // update
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        quit = true;
      }
    }
    // render

    renderer.SetColor(0.f, 0.f, 0.f, 255.f); // Set draw color to black

    renderer.Clear(); // Clear the screen

    // Draw a random point
    for (size_t i = 0; i < v.size(); ++i) {
      renderer.SetColor(static_cast<Uint8>(Engine::RandomInt(256)),
                        Engine::RandomInt(256), Engine::RandomInt(256), 255);
      renderer.DrawPoint(Engine::RandomInt(window.window_width),
                         Engine::RandomInt(window.window_height));
    }

    // Draw a random line
    for (int i = 0; i < 10; ++i) {
      renderer.SetColor(static_cast<Uint8>(Engine::RandomInt(256)),
                        Engine::RandomInt(256), Engine::RandomInt(256), 255);
      renderer.DrawLine(Engine::RandomInt(window.window_width),
                        Engine::RandomInt(window.window_height),
                        Engine::RandomInt(window.window_width),
                        Engine::RandomInt(window.window_height));
    }

    // Draw a random rectangle
    for (int i = 0; i < 5; ++i) {
      renderer.SetColor(static_cast<Uint8>(Engine::RandomInt(256)),
                        Engine::RandomInt(256), Engine::RandomInt(256), 255);
      renderer.DrawFillRect(Engine::RandomInt(window.window_width),
                            Engine::RandomInt(window.window_height),
                            Engine::RandomInt(100 + 20),
                            Engine::RandomInt(100 + 20));
    }

    renderer.SetColor(static_cast<Uint8>(Engine::RandomInt(256)),
                      Engine::RandomInt(256), Engine::RandomInt(256), 255);
    renderer.DrawText("Hello, World!", 10.0f, 10.0f, 100.0f,
                      30.0f); // Draw the text (placeholder)

    renderer.Present(); // Present the rendered content to the
                        // screen
  }
  // SHUTDOWN

  renderer.Destroy(); // Clean up the renderer and window

  return 0;
}
