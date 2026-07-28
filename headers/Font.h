//
// Created by brett on 7/28/26.
//

#pragma once
#include <string>

struct TTF_Font;

namespace Engine {
    class Font {
    public:
        Font() = default;
        ~Font();

        bool Load(const std::string& name, float fontSize);

    private:
        friend class Text;

        TTF_Font* m_ttfFont{ nullptr };
    };
}
