#pragma once
#include "random.h"
#include "vector2.h"

namespace Engine {
    struct Transform {
        Engine::Vector2 position;
        float           rotation;
        float           scale;
    };
} // namespace Engine
