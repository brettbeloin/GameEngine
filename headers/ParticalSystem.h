//
// Created by brett on 7/29/26.
//

#pragma once
#include "vector2.h"
#include "vector3.h"
#include <vector>

namespace Engine {
    struct Particle {
        bool    active{false};
        float   lifespan{1};

        Vector2 position{0, 0};
        Vector2 velocity{0, 0};
        Color   color{0, 0, 0};
    };

    class ParticleSystem {
      public:
        ParticleSystem() = default;

        bool Initialize(size_t poolSize = 1000);
        void Shutdown();

        void Update(float dt);
        void Draw(class Renderer &renderer);

        void AddParticle(Particle &particle);

      private:
        Particle *GetFreeParticle();

      private:
        // store particles in particle pool
        std::vector<Particle> m_particles;
    };
} // namespace Engine
