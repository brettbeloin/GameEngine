#include "GameTime.h"

#include <SDL3/SDL.h>
#include <pch.h>

Engine::Time::Time() {
    Reset();
}

void Engine::Time::Reset() {
    m_start_ticks = SDL_GetTicksNS();
    m_frame_ticks = SDL_GetTicksNS();
    m_current_ticks = SDL_GetTicksNS();
}

void Engine::Time::Tick() {
    m_current_ticks = SDL_GetTicksNS();
    m_delta_ticks = m_current_ticks - m_frame_ticks;
    m_frame_ticks = m_current_ticks;
}
