# For more information about build system see
# https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html
cmake_minimum_required(VERSION 3.19)

if(CMAKE_BUILD_TYPE STREQUAL "Desktop-Debug")
    message(STATUS "Desktop-Debug Build")
    add_definitions(-DDESKTOP)
    set(CMAKE_CXX_FLAGS_DEBUG "-g")

elseif(CMAKE_BUILD_TYPE STREQUAL "Desktop-Release")
    message(STATUS "Desktop-Release build (optimized for size)")
    add_definitions(-DDESKTOP)
    set(CMAKE_CXX_FLAGS_RELEASE "-Os -flto -fPIC -fdata-sections -ffunction-sections -fno-exceptions  -Wl,--gc-sections -flto")

elseif(CMAKE_BUILD_TYPE STREQUAL "Esp32-Debug")
    message(STATUS "Esp32-Debug Build")
    add_definitions(-DESP_PLATFORM)
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    include($ENV{IDF_PATH}/tools/cmake/project.cmake)

elseif(CMAKE_BUILD_TYPE STREQUAL "Esp32-Release")
    message(STATUS "Esp32-Release Build")
    add_definitions(-DESP_PLATFORM)
    include($ENV{IDF_PATH}/tools/cmake/project.cmake)
    
else()
    message( FATAL_ERROR "Please, specify a build type" )
endif()

project(flappy VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(core platform)

if(PLATFORM STREQUAL "Desktop")
    include(_cmake/CPM.cmake)
    CPMAddPackage("gh:raysan5/raylib#5.0")

    add_library(core STATIC
        core/scenario/scenario.cpp
        core/game/game.cpp
        core/pipe/pipe.cpp
        core/player/player.cpp
        core/score/score.cpp
        core/sprite/sprite.cpp)
    
    add_executable(flappy 
        main/main.cpp
        core/interface/renderer.cpp
        core/interface/inputer.cpp)

    target_link_libraries(flappy PRIVATE core raylib)
    target_compile_options(flappy PRIVATE -Wall -Wextra -Wpedantic -Werror)

elseif(PLATFORM STREQUAL "Esp32")
    add_library(core STATIC
        core/scenario/scenario.cpp
        core/game/game.cpp
        core/pipe/pipe.cpp
        core/player/player.cpp
        core/score/score.cpp
        core/sprite/sprite.cpp)

    add_executable(flappy 
        main/main.cpp
        core/interface/renderer.cpp
        core/interface/inputer.cpp)

    target_link_libraries(flappy PRIVATE core)
    target_compile_options(flappy PRIVATE -Wall -Wextra -Wpedantic -Werror)

else()
    message( FATAL_ERROR "Please, specify a platform" )

endif()
