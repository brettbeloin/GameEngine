#pragma once
#include <cstdlib>

namespace Engine {
inline int RandomInt() { return rand(); }

/// <summary>
/// Get random integer [0, max)
/// </summary>
/// <param name="max">exclusive max</param>
/// <returns>Random number between 0  and max </returns>
inline int RandomInt(int max) { return rand() % max; }

/// <summary>
/// Get A random number between (min and max)
/// </summary>
/// <param name="min">minum value</param>
/// <param name="max">maxamum value</param>
/// <returns>Random number between min and max </returns>
inline int RandomInt(int min, int max) {
  return min + rand() % (max - min) + 1;
}

inline float RandomFloat() { return rand() / static_cast<float>(RAND_MAX); }

inline float RandomFloat(float max) { return RandomFloat() * max; }

inline float RandomFloat(float min, float max) {
  return min + (RandomFloat() * (max - min));
}
} // namespace Engine
