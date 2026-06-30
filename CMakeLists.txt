cmake_minimum_required(VERSION 3.20)
project(GameEngine CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(external/SDL3)

add_library(Engine STATIC
    Engine/Engine.cpp
    )

target_include_directories(Engine PUBLIC headers/)
target_link_libraries(Engine PUBLIC SDL3::SDL3)

add_executable(GameEngine)

target_sources(GameEngine PRIVATE
    src/Game.cpp
    )

target_link_libraries(GameEngine PRIVATE Engine)

