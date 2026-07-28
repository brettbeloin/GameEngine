cmake_minimum_required(VERSION 3.20)
project(GameEngine C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(external/SDL3)
add_subdirectory(external/json)

add_library(Engine STATIC
    Engine/Engine.cpp
    Engine/Renderer.cpp
    Engine/Input.cpp
    Engine/GameTime.cpp
    Engine/Actor.cpp
    Engine/Player.cpp
    Engine/Enemy.cpp
    Engine/Scene.cpp
    Engine/Assets.cpp
    Engine/File.cpp
    Engine/Database.cpp
    Engine/Model.cpp
    Engine/Mesh.cpp
    Engine/Audio.cpp
    Engine/Bullet.cpp

    external/sqlite/sqlite3.c
)

target_include_directories(Engine PUBLIC
    headers/
    external/sqlite
)
target_link_libraries(Engine PUBLIC
    SDL3::SDL3
    Fmod
    nlohmann_json::nlohmann_json

)

add_executable(GameEngine)

if (WIN32)
    # Windows
    MESSAGE ("Compiling for Windows")
    add_library(Fmod SHARED IMPORTED)
    set_property(TARGET Fmod PROPERTY
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/external/fmod_windows/api/core/inc/")

    set_property(TARGET Fmod PROPERTY
        IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/external/fmod_windows/api/core/lib/x86/fmod.dll")

    set_property(TARGET Fmod PROPERTY
        IMPORTED_IMPLIB "${CMAKE_SOURCE_DIR}/external/fmod_windows/api/core/lib/x86/fmod_vc.lib")

    add_custom_command(TARGET GameEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/external/fmod_windows/api/core/lib/x86/fmod.dll"
            $<TARGET_FILE_DIR:GameEngine>
    )

    add_custom_command(TARGET GameEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL3-shared>
            $<TARGET_FILE_DIR:GameEngine>
    )

    add_custom_command(TARGET GameEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/Assets"
    "$<TARGET_FILE_DIR:GameEngine>/Assets"
)
elseif (UNIX)
    # Linux
    MESSAGE ("Compiling for Linux")
    add_library(Fmod SHARED IMPORTED)
    set_property(TARGET Fmod PROPERTY
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/external/fmod_linux/api/core/inc/")
    set_property(TARGET Fmod PROPERTY
        IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/external/fmod_linux/api/core/lib/x86_64/libfmod.so")

endif()

target_sources(GameEngine PRIVATE
        Game/Main.cpp
    )

target_link_libraries(GameEngine PRIVATE Engine)
