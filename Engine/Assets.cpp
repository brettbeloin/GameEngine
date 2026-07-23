//
// Created by brett on 7/22/26.
//
#include "Assets.h"

using namespace Engine;

    namespace Assets {
        // mesh / model
        const Mesh player_mesh{
            {
                {5, 0},
                {3, -3},
                {1, -3},
                {-1, -2},
                {0, -1},
                {-2, 1},
                {1, 1},
                {5, 0},
                },
               Color{1.0, 0.0, 0.0}
        };
         Model player_model = std::vector{player_mesh};
    }
