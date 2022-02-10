cmake_minimum_required(VERSION 3.19)
project(tanks LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

add_executable(tanks
        entities/Entity.cpp
        entities/Entity.hpp
        entities/Player.cpp
        entities/Player.hpp
        lib/Game.hpp
        lib/Game.cpp
        lib/State.cpp
        lib/State.hpp
        lib/GraphicsSettings.cpp
        lib/GraphicsSettings.hpp
        GUI/PauseMenu.cpp
        GUI/PauseMenu.hpp
        Map/TileMap.cpp
        Map/TileMap.hpp
        Map/Tile.hpp
        Map/Tile.cpp
        gui-components/gui.cpp
        gui-components/gui.hpp
        components/HitboxComponent.cpp
        components/HitboxComponent.hpp
        components/AnimationComponent.cpp
        components/AnimationComponent.hpp
        components/MovementComponent.cpp
        components/MovementComponent.hpp
        states/EditorState.cpp
        states/EditorState.hpp
        states/GameState.cpp
        states/GameState.hpp
        states/MainMenuState.cpp
        states/MainMenuState.hpp
        states/SettingsState.cpp
        states/SettingsState.hpp
        main.cpp)

include_directories(SFML-2.5.1-macos-clang/include)
find_package(SFML 2.4 COMPONENTS system window graphics REQUIRED)

target_link_libraries(tanks sfml-graphics)
