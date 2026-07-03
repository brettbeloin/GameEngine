#include "../Engine/Engine.cpp"
#include "Engine.h"
#include <SDL3/SDL.h>
#include <iostream>

int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_VIDEO);
  int window_width, window_height;
  window_width = window_height = 500;

  SDL_Window *window =
      SDL_CreateWindow("Game Engine", window_width, window_height, 0);
  if (window == nullptr) {
    std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
  if (renderer == nullptr) {
    std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  SDL_Event e;
  bool quit = false;

  // Define a rectangle
  SDL_FRect greenSquare{(static_cast<float>(window_width) / 2) - (50.0f / 2),
                        (static_cast<float>(window_height) / 2) - (50.05f / 2),
                        50.0f, 50.0f}; // x, y, width, height

  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_EVENT_QUIT) {
        quit = true;
      } else if (e.type == SDL_EVENT_WINDOW_RESIZED) {
        // Update tracking variables with the new dimensions
        window_width = e.window.data1;
        window_height = e.window.data2;

        // Recalculate X and Y positions to keep the square centered
        greenSquare.x =
            (static_cast<float>(window_width) / 2.0f) - (greenSquare.w / 2.0f);
        greenSquare.y =
            (static_cast<float>(window_height) / 2.0f) - (greenSquare.h / 2.0f);
      }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0,
                           255); // Set render draw color to black
    SDL_RenderClear(renderer);   // Clear the renderer

    SDL_SetRenderDrawColor(renderer, 0, 255, 0,
                           255); // Set render draw color to green
    SDL_RenderFillRect(renderer, &greenSquare); // Render the rectangle

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Set text Color to red
    SDL_RenderDebugText(renderer, 10, 10,
                        Engine::fnEngine()); // Render the text

    SDL_RenderPresent(renderer); // Render the screen
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
