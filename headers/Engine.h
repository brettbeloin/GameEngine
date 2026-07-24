#pragma once

#include "MathUtils.h"
#include "Transform.h"
#include "random.h"
#include "vector2.h"
#include "vector3.h"

// systems
#include <iostream>

#include "GameTime.h"
#include "Input.h"
#include "renderer.h"

#include "Actor.h"
#include "File.h"
#include "Scene.h"

namespace Engine {
    class Engine {
      public:
        static Engine &GetEngine() {
            static Engine engine;
            return engine;
        }

        bool   Initialize();
        void   Destroy();

        void   Update();

        Input &GetInput() {
            return m_input;
        };

        void SetInput(const Input &input) {
            m_input = input;
        };

        Renderer &GetRenderer() {
            return m_renderer;
        }

        void SetRenderer(const Renderer &renderer) {
            m_renderer = renderer;
        }

        Time &GetTime() {
            return m_time;
        }

        void SetTime(const Time &time) {
            m_time = time;
        }

        Window &GetWindow() {
            return m_window;
        }

        void SetWindow(const Window &window) {
            m_window = window;
        }

      private:
        Engine() = default;

      private:
        Input    m_input;
        Renderer m_renderer;

        Time     m_time;

        Window   m_window;
    };

} // namespace Engine
