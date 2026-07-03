#pragma once
#include "SDL3/SDL.h"
#include "pch.h"

namespace Engine {
// class Window;
class Renderer;

struct Window {
  const char *window_title;
  int window_width, window_height;
  // SDL_Window* sdlWindow; // Pointer to the SDL window
};

class Renderer {
private:
  SDL_Window *m_window = nullptr;     // Pointer to the SDL window
  SDL_Renderer *m_renderer = nullptr; // Pointer to the SDL renderer

public:
  bool Initialize(const Window &window);
  // Renderer(int width, int height);
  // ~Renderer();

  void Clear();
  void Present();
  void SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
  void DrawRect(const SDL_FRect &rect) const;
  void Destroy(); // Method to destroy the renderer and window
};
} // namespace Engine
