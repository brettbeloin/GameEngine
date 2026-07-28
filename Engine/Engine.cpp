#include "Engine.h"
#include "Database.h"
#include <iostream>

namespace Engine {
    bool Engine::Initialize() {
        m_window = {"Game Engine", 500, 500}; // Set the window width and height

        if (!m_renderer.Initialize(GetWindow())) {
            std::cerr << "Failed to initialize the renderer." << std::endl;
            return false;
        }

        if (!m_input.Initialize()) {
            std::cerr << "Failed to initialize input." << std::endl;
            return false;
        }

        if (!Database::Database::GetDatabase().Init()) {
            std::cerr << "Failed to initialize input." << std::endl;
            return false;
        }

        if (!m_audio.Initialize()) {
            std::cerr << "Failed to initialize input." << std::endl;
            return false;
        }

        return true;
    }

    void Engine::Destroy() {
        m_input.Destroy();
        m_audio.Shutdown();
        Database::Database::GetDatabase().Destroy();
        m_renderer.Destroy();
    }

    void Engine::Update() {
        m_input.Update();
        m_audio.Update();
        m_time.Tick();
    }
} // namespace Engine
