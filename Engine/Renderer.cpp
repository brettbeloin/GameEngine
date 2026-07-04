#include "renderer.h"
#include <iostream>

bool Engine::Renderer::Initialize(const Engine::Window &window) {
  // Initialization code for the renderer
  SDL_Init(SDL_INIT_VIDEO);

  m_window = SDL_CreateWindow(window.window_title, window.window_width,
                              window.window_height, 0);
  if (m_window == nullptr) {
    std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return false;
  }

  m_renderer = SDL_CreateRenderer(m_window, NULL);
  if (m_renderer == nullptr) {
    std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(m_window);
    SDL_Quit();
    return false;
  }

  return true; // Return true if initialization is successful
}

void Engine::Renderer::Clear() { SDL_RenderClear(m_renderer); }

void Engine::Renderer::Present() { SDL_RenderPresent(m_renderer); }

void Engine::Renderer::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
  SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
}

void Engine::Renderer::DrawRect(float x, float y, float w, float h) const {
  SDL_FRect rect = {x, y, w, h};
  SDL_RenderRect(m_renderer, &rect); // Render the rectangle
}

void Engine::Renderer::DrawFillRect(float x, float y, float w, float h) const {
  SDL_FRect rect = {x, y, w, h};
  SDL_RenderFillRect(m_renderer, &rect); // Render the rectangle
}

void Engine::Renderer::DrawPoint(float x, float y) const {
  SDL_RenderPoint(m_renderer, x, y);
}

void Engine::Renderer::DrawText(const char *text, float x, float y, float w,
                                float h) const {
  // Placeholder for text rendering
  // In a real implementation, you would use a library like SDL_ttf to render
  // text
  SDL_RenderDebugText(m_renderer, x, y, text); // Render the text
}

void Engine::Renderer::Destroy() {
  if (m_renderer) {
    SDL_DestroyRenderer(m_renderer);
    m_renderer = nullptr;
  }
  if (m_window) {
    SDL_DestroyWindow(m_window);
    m_window = nullptr;
  }
  SDL_Quit();
}
