//
// Created by brett on 7/28/26.
//

#pragma once
#include "Font.h"
#include "vector3.h"

struct SDL_Texture;
namespace Engine {
    class Renderer;
    // class Color;

    class Text {
      public:
        Text() = default;
        Text(Font *font) : m_font{font} {
        }
        ~Text();

        bool Create(Renderer &renderer, const std::string &text, const Color &color);
        void Draw(const Renderer &renderer, float x, float y);

      private:
        Font        *m_font{nullptr};
        SDL_Texture *m_texture{nullptr};
    };
} // namespace Engine
