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
         {-6.6, -8.05},
         {-5.3, -5.6},
         {-6.9, -4},
         {-0.1, -4.1},
         {-6.4, -8.1},
         },
        Color{1.0, 0.0, 0.0}
    };

    const Mesh mesh2 = {
        {{0, -4}, {0, -1}, {4, -2}, {4, -5}, {0, -4}},
        Color{0.0, 1.0, 0.0}
    };

    Model player_model = std::vector{player_mesh, mesh2};
} // namespace Assets
