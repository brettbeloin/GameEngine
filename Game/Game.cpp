#include "Engine.h"
// #include "SDL3/SDL.h"

#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[]) {
  Engine::Renderer renderer;
  constexpr Engine::Window window = {"Game Engine", 500,
                                     500}; // Set the window width and height

  if (const bool initSuccess = renderer.Initialize(window); !initSuccess) {
    std::cerr << "Failed to initialize the renderer." << std::endl;
    return -1;
  }

  std::cout << "Successfully initialized the renderer." << std::endl;

  SDL_Event e;
  bool quit = false;

  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_EVENT_QUIT) {
        quit = true;
      }
    }

    renderer.SetColor(0, 0, 0, 255); // Set draw color to black

    renderer.Clear(); // Clear the screen

    for (int i = 0; i < 100; ++i) {
      renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 255);
      renderer.DrawPoint(rand() % window.window_width,
                         rand() % window.window_height); // Draw a random point
    }

    renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 255);
    renderer.DrawFillRect(
        (static_cast<float>(window.window_width) / 2) - (50.0f / 2),
        (static_cast<float>(window.window_height) / 2) - (50.05f / 2), 50.0f,
        50.0f); // Draw the rectangle

    renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 255);
    renderer.DrawText("Hello, World!", 10.0f, 10.0f, 100.0f,
                      30.0f); // Draw the text (placeholder)

    renderer.Present(); // Present the rendered content to the screen
  }

  renderer.Destroy(); // Clean up the renderer and window

  return 0;
}
