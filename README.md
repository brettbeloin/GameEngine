This is the Game engine as of right now 6/30/26.

# Build the Project
- `cd GameEngine`
- `git submodule update --init --recursive`
- `cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON`
- `cmake --build build`
- `./build/GameEngine`
