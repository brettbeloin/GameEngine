cmake_minimum_required(VERSION 3.20)
project(GameEngine CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(external/SDL3)

if (WIN32)
    # Windows
    add_library(Fmod SHARED IMPORTED)
    set_property(TARGET Fmod PROPERTY
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/external/fmod_windows/api/core/inc/")

    set_property(TARGET Fmod PROPERTY
        IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/external/fmod_windows/FMOD SoundSystem/FMOD Studio API Windows/api/core/lib/x86/libfmod.dll")
elseif (UNIX)
    # Linux
    add_library(Fmod SHARED IMPORTED)
    set_property(TARGET Fmod PROPERTY
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/external/fmod_linux/api/core/inc/")
    set_property(TARGET Fmod PROPERTY
        IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/external/fmod_linux/api/core/lib/x86_64/libfmod.so")

endif()

add_library(Engine STATIC
    Engine/Engine.cpp
    Engine/Renderer.cpp
    Engine/Input.cpp
    Engine/GameTime.cpp
    Engine/Actor.cpp
    # Engine/Player.cpp
    )

target_include_directories(Engine PUBLIC headers/)
target_link_libraries(Engine PUBLIC SDL3::SDL3 Fmod)

add_executable(GameEngine)

target_sources(GameEngine PRIVATE
    Game/Game.cpp
    )

target_link_libraries(GameEngine PRIVATE Engine)
