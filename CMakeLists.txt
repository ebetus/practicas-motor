cmake_minimum_required(VERSION 3.16)
project(practica03_motor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Detección de SDL3
find_package(SDL3 QUIET)
if(NOT SDL3_FOUND)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL3 REQUIRED IMPORTED_TARGET sdl3)
set(SDL3_TARGET PkgConfig::SDL3)
else()
set(SDL3_TARGET SDL3::SDL3)
endif()

# Declaración de headers y fuentes
set(HEADERS
include/core/Component.hpp
include/core/GameObject.hpp
include/core/Scene.hpp
include/core/SceneManager.hpp
include/core/Vector2.hpp
include/components/TransformComponent.hpp
include/components/BallComponent.hpp
include/components/ColliderComponent.hpp
include/components/PatrolComponent.hpp
include/components/PlayerControllerComponent.hpp
include/components/RectRenderComponent.hpp
include/core/CollisionManager.hpp
include/scenes/GameOverScene.hpp
include/scenes/GameScene.hpp
include/scenes/PauseScene.hpp
include/scenes/TitleScene.hpp
)

set(FUENTES
src/main.cpp
src/core/CollisionManager.cpp
src/core/Component.cpp
src/core/GameObject.cpp
src/core/Scene.cpp
src/core/SceneManager.cpp
src/core/Vector2.cpp
src/components/TransformComponent.cpp
src/components/BallComponent.cpp
src/components/ColliderComponent.cpp
src/components/PatrolComponent.cpp
src/components/PlayerControllerComponent.cpp
src/components/RectRenderComponent.cpp
src/scenes/GameOverScene.cpp
src/scenes/GameScene.cpp
src/scenes/PauseScene.cpp
src/scenes/TitleScene.cpp
)

add_executable(${PROJECT_NAME} ${HEADERS} ${FUENTES})

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL3_TARGET})