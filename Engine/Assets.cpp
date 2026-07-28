//
// Created by brett on 7/22/26.
//
#include "Assets.h"
#include "vector3.h"

using namespace Engine;

namespace Assets {
    // mesh / model
    const Mesh player_mesh{
        {
         {2, 0},
         {-2, 2},
         {-1, 0},
         {-2, -2},
         {2, 0},
         },
        Color{1.0, 0.0, 0.0}
    };

    const Mesh enemy_mesh{
        {
         {-2, -6},
         {2, -6},
         {3, -4},
         {3, -1},
         {2, 1},
         {-2, 1},
         {-3, -1},
         {-3, -4},
         {-2, -6},
         },
        Color{0.4, 0.3, 0.1}
    };

    const Mesh bullet_mesh = {
        {
         {1, 0},
         {0, 1},
         {0, -1},
         {1, 0},
         },
        Color{     0.0, 1.0, 0.0 }
    };

    Model player_model = std::vector{player_mesh};

    Model enemy_model = std::vector{enemy_mesh};

    Model bullet_model = std::vector{bullet_mesh};
} // namespace Assets
