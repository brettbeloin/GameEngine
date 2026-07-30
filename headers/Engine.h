#pragma once

#include "File.h"
#include "MathUtils.h"
#include "Text.h"
#include "Transform.h"
#include "random.h"
#include "vector2.h"
#include "vector3.h"

// systems

#include "Audio.h"
#include "GameTime.h"
#include "Input.h"
#include "ParticalSystem.h"
#include "renderer.h"

// framework
#include "Actor.h"
#include "Game.h"
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

        Audio &GetAudio() {
            return m_audio;
        }
        ParticleSystem &GetPS() {
            return m_particleSystem;
        }

        Engine(const Engine &) = delete;
        Engine &operator=(const Engine &) = delete;

      private:
        Engine() = default;

      private:
        Input          m_input;
        Renderer       m_renderer;

        Time           m_time;

        Window         m_window;
        Audio          m_audio;

        ParticleSystem m_particleSystem;
    };

} // namespace Engine
