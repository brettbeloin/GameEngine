//
// Created by brett on 7/21/26.
//

#pragma once
#include <vector>

namespace Engine {
    class Actor;

    class Scene {
        public:
        Scene() = default;

        void AddActor(Actor* actor) {
            m_actors.push_back(actor);
        };

        void Update(float dt);
        void Draw(const class Renderer& renderer) const;

        private:
        std::vector<Actor *> m_actors;
    };
}
