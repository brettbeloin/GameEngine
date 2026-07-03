#include "Engine.h"
// #include "SDL3/SDL.h"

#include <iostream>

int main(int argc, char *argv[]) {
  Engine::Renderer r;
  constexpr Engine::Window window = {"Game Engine", 500,
                                     500}; // Set the window width and height

  if (const bool initSuccess = r.Initialize(window); !initSuccess) {
    std::cerr << "Failed to initialize the renderer." << std::endl;
    return -1;
  }

  std::cerr << "Successfully initialized the renderer." << std::endl;

  SDL_Event e;
  bool quit = false;

  // Define a rectangle
  constexpr SDL_FRect greenSquare{
      (static_cast<float>(window.window_width) / 2) - (50.0f / 2),
      (static_cast<float>(window.window_height) / 2) - (50.05f / 2), 50.0f,
      50.0f}; // x, y, width, height

  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_EVENT_QUIT) {
        quit = true;
      }
    }

    r.SetDrawColor(0, 0, 0, 255); // Set draw color to black

    r.Clear(); // Clear the screen

    r.SetDrawColor(0, 255, 0, 255); // Set draw color to green
    r.DrawRect(greenSquare);        // Draw the rectangle
    r.Present(); // Present the rendered content to the screen
  }

  r.Destroy(); // Clean up the renderer and window

  return 0;
}
