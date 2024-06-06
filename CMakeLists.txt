cmake_minimum_required(VERSION 3.19)
project(Flappy VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build options
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug build")
    add_definitions(-DDEBUG_BUILD)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Release build - for size optimization")
    set(CMAKE_CXX_FLAGS_RELEASE "-Os -fdata-sections -ffunction-sections -fno-exceptions -Wl,--gc-sections")
else()
    message( FATAL_ERROR "Specify a build type" )
endif()

add_executable(Flappy 
    app/source/main.cpp
    core/source/scenario/scenario.cpp
    core/source/game/game.cpp
    core/source/pipe/pipe.cpp
    core/source/player/player.cpp
    core/source/score/score.cpp
    core/source/sprite/sprite.cpp
    core/source/sound/sound.cpp
    # core/source/network/network.cpp
    # core/source/pubsub/pubsub.cpp
)

target_include_directories(Flappy PRIVATE include core core/source)

# Platform-specific configurations
if(PLATFORM STREQUAL "Desktop")
    add_definitions(-DDESKTOP)

    include(_cmake/CPM.cmake)
    CPMAddPackage("gh:raysan5/raylib#5.0")

    # set(THREADS_PREFER_PTHREAD_FLAG ON)
    # find_package(Threads REQUIRED)
    # target_link_libraries(Flappy PRIVATE raylib Threads::Threads)

    target_link_libraries(Flappy PRIVATE raylib)
elseif(PLATFORM STREQUAL "ESP32")
    add_definitions(-DESP32)
    # Add ESP32 specific configurations
    # include_directories(${ESP32_INCLUDE_DIR})
    # target_link_libraries(FlappyTemplate ${ESP32_LIBRARIES})
endif()
