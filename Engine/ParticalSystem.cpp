//
// Created by brett on 7/29/26.
//

#include "ParticalSystem.h"
#include "renderer.h"

namespace Engine {
    bool ParticleSystem::Initialize(size_t size) {
        m_particles.resize(size);

        return true;
    }

    void ParticleSystem::Shutdown() {
        m_particles.clear();
    }

    void ParticleSystem::Update(float dt) {
        for (auto &particle : m_particles) {
            if (!particle.active) {
                continue;
            }

            particle.lifespan -= dt;

            particle.active = (particle.lifespan > 0);

            particle.position += particle.velocity * dt;
        }
    }

    void ParticleSystem::Draw(Renderer &renderer) {
        for (auto &particle : m_particles) {
            if (particle.active) {
                // set particle color and draw point at current position
                // TODO: set color with particle color
                // TODO: draw point with particle position

                renderer.SetColor(particle.color.r, particle.color.g, particle.color.b, 255);
                renderer.DrawPoint(particle.position.x, particle.position.y);
            }
        }
    }

    void ParticleSystem::AddParticle(Particle &particle) {
        Particle *freeParticle = GetFreeParticle();

        if (freeParticle) {
            *freeParticle = particle;

            freeParticle->active = true;
        }
    }

    Particle *ParticleSystem::GetFreeParticle() {
        for (auto &particle : m_particles) {
            if (!particle.active) {
                return &particle;
            }

            return nullptr;
        }

        return nullptr;
    }
} // namespace Engine
