#pragma once
#include "vector2.h"

namespace Engine {
    struct Transform {
        Engine::Vector2 position = {250, 250};
        float           rotation;
        float           scale;
    };
} // namespace Engine
