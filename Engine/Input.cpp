#include "Input.h"
#include "pch.h"
#include <SDL3/SDL.h>

bool Engine::Input::Initialize() {
    int         num_keys;
    const bool *key_state = SDL_GetKeyboardState(&num_keys);

    m_key_states.resize(num_keys);

    std::copy(key_state, key_state + num_keys, m_key_states.begin());
    m_pre_key_states = m_key_states;

    return true;
}

void Engine::Input::Destroy() {
}

void Engine::Input::Update() {
    m_pre_key_states = m_key_states;
    const bool *key_state = SDL_GetKeyboardState(NULL);
    std::copy(key_state, key_state + m_key_states.size(), m_key_states.begin());

    m_pre_button_states = m_button_states;
    m_button_states = SDL_GetMouseState(&m_mouse_pos.x, &m_mouse_pos.y);
}

uint32_t Engine::Input::GetButtonBit(MouseButton button) const {
    return SDL_BUTTON_MASK(static_cast<uint32_t>(button));
};
