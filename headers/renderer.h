#pragma once
#include "SDL3/SDL.h"
#include "pch.h"

namespace Engine {
    class Renderer;

    struct Window {
        const char *window_title;
        int         window_width, window_height;
    };

    class Renderer {
      private:
        SDL_Window   *m_window = nullptr;   // Pointer to the SDL window
        SDL_Renderer *m_renderer = nullptr; // Pointer to the SDL renderer

      public:
        bool Initialize(const Window &window);
        void Destroy();

        void Clear() const;
        void Present() const;

        void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;
        void SetColor(float r, float g, float b, float a) const;

        void DrawFillRect(float x, float y, float w, float h) const;
        void DrawRect(float x, float y, float w, float h) const;
        void DrawPoint(float x, float y) const;
        void DrawText(const char *text, float x, float y, float w, float h) const;
        void DrawLine(float x1, float y1, float x2, float y2) const;

        void DrawModel(const class Model &model, const struct Transform &Transform) const;
    };
} // namespace Engine
