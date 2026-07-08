#pragma once

#include <cstdint>
namespace Engine {
    class Time {
      public:
        Time();

        void  Reset();
        void  Tick();

        float GetTime() {
            return TicksToSeconds(m_current_ticks - m_start_ticks);
        };

        float GetDeltaTime() {
            return TicksToSeconds(m_delta_ticks);
        }

        float TicksToSeconds(uint64_t ticks) {
            return static_cast<float>(ticks) / 100'000'000;
        }

      private:
        uint64_t m_start_ticks = 0;
        uint64_t m_current_ticks = 0;
        uint64_t m_frame_ticks = 0;
        uint64_t m_delta_ticks = 0;
    };
} // namespace Engine
