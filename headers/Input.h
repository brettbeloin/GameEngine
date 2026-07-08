#pragma once

#include "vector2.h"
#include <cstdint>
#include <vector>
namespace Engine {
    class Input {
      public:
        enum class MouseButton { LEFT = 1, MIDDLE, RIGHT, x1, x2 };

      public:
        bool Initialize();
        void Destroy();

        void Update();

        bool GetKeyDown(int key) const {
            return m_key_states[key];
        }

        bool GetPreKeyDown(int key) const {
            return m_key_states[key];
        }

        bool GetKeyPressed(int key) const {
            return !m_pre_key_states[key] && m_key_states[key];
        }

        bool GetPreKeyPressed(int key) const {
            return !m_key_states[key] && m_pre_key_states[key];
        }

        bool GetButtonDown(MouseButton button) {
            return m_button_states & GetButtonBit(button);
        }

        bool GetPreButtonDown(MouseButton button) {
            return m_pre_button_states & GetButtonBit(button);
        }

        bool GetButtonPressed(MouseButton button) {
            return !GetPreButtonDown(button) && GetButtonDown(button);
        }

        bool GetButtonReleased(MouseButton button) {
            return GetPreButtonDown(button) && !GetButtonDown(button);
        }

        Vector2 GetMousePosition() {
            return m_mouse_pos;
        }

      private:
        // KeyBoard
        std::vector<bool> m_key_states;
        std::vector<bool> m_pre_key_states;

        // mouse
        uint32_t m_button_states = 0;
        uint32_t m_pre_button_states = 0;
        Vector2  m_mouse_pos;
        uint32_t GetButtonBit(MouseButton button) const;
    };
} // namespace Engine
