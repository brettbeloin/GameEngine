//
// Created by brett on 7/28/26.
//

#pragma once
#include "Scene.h"

namespace Engine {
    class Game {
      public:
        Game() = default;

        explicit Game(Scene *scene) : m_scene{scene} {};

        virtual bool Initialize() {
            return true;
        }
        virtual void Destroy() {
        }

        virtual void Update(float st);
        virtual void Draw(Renderer &renderer);

        void         SetScene(Scene *scene) {
            m_scene = scene;
        };

      protected:
        Scene *m_scene = nullptr;
    };
} // namespace Engine
