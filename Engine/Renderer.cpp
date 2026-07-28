#include "renderer.h"
#include "Model.h"
#include "SDL3/SDL_render.h"
#include "Transform.h"
#include <iostream>

#include "MathUtils.h"

bool Engine::Renderer::Initialize(const Engine::Window &window) {
    // Initialization code for the renderer
    SDL_Init(SDL_INIT_VIDEO);

    if (!TTF_Init()) {
        std::cerr << "TTF_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    m_window = SDL_CreateWindow(window.window_title, window.window_width, window.window_height, 0);
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

    SDL_SetRenderVSync(m_renderer, 1);

    return true; // Return true if initialization is successful
}

void Engine::Renderer::Clear() const {
    SDL_RenderClear(m_renderer);
}

void Engine::Renderer::Present() const {
    SDL_RenderPresent(m_renderer);
}

void Engine::Renderer::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const {
    SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
}

void Engine::Renderer::SetColor(float r, float g, float b, float a) const {
    SDL_SetRenderDrawColorFloat(m_renderer, r, g, b, a);
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

void Engine::Renderer::DrawText(const char *text, float x, float y, float w, float h) const {
    // Placeholder for text rendering
    // In a real implementation, you would use a library like SDL_ttf to render
    // text
    SDL_RenderDebugText(m_renderer, x, y, text); // Render the text
}

void Engine::Renderer::DrawLine(float x1, float y1, float x2, float y2) const {
    SDL_RenderLine(m_renderer, x1, y1, x2, y2);
}

void Engine::Renderer::DrawModel(const Model& model, const Transform& transform) const
{
    for (auto mesh : model.GetMeshes())
    {
        SetColor(mesh.GetColor().r, mesh.GetColor().g, mesh.GetColor().b, 1.0f);
        auto& points = mesh.GetPoints();
        for (int i = 0; i + 1 < points.size(); i++)
        {
            // local space
            Vector2 v1 = points[i];
            Vector2 v2 = points[i + 1];

            // convert to world space
            v1 *= transform.scale;
            v2 *= transform.scale;

            v1 = v1.Rotate(transform.rotation * DegToRad);
            v2 = v2.Rotate(transform.rotation * DegToRad);

            v1 += transform.position;
            v2 += transform.position;

            DrawLine(v1.x, v1.y, v2.x, v2.y);
        }
    }
}


void Engine::Renderer::Destroy() {
    TTF_Quit();
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
