#include "Engine.h"
#include <iostream>

namespace Engine {
    Engine g_engine;

    bool   Engine::Initialize() {
        m_window = {"Game Engine", 500, 500}; // Set the window width and height

        if (!m_renderer.Initialize(GetWindow())) {
            std::cerr << "Failed to initialize the renderer." << std::endl;
            return false;
        }

        if (!m_input.Initialize()) {
            std::cerr << "Failed to initialize input." << std::endl;
            return false;
        }

        return true;
    }

    void Engine::Destroy() {
        m_input.Destroy();
        m_renderer.Destroy();
    }

    void Engine::Update() {
        m_input.Update();
        m_time.Tick();
    }
} // namespace Engine
