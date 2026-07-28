//
// Created by brett on 7/21/26.
//

#pragma once
#include <string>
#include <vector>

namespace Engine {
    class Actor;

    class Scene {
      public:
        Scene() = default;

        void                     AddActor(Actor *actor);

        void                     Update(float dt);
        void                     Draw(const class Renderer &renderer) const;

        template <typename T> T *GetActorByName(const std::string &name);

      private:
        void UpdateCollisions();

      private:
        std::vector<Actor *> m_actors;
        std::vector<Actor *> m_pendingActors;
    };

    template <typename T = Actor> T *Scene::GetActorByName(const std::string &name) {
        for (Actor *actor : m_actors) {
            T *actor_t = dynamic_cast<T *>(actor);

            if (actor_t && actor_t->m_name == name) {
                return actor_t;
            }
        }

        return nullptr;
    }
} // namespace Engine
