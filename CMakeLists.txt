# For more information about build system see
# https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html
cmake_minimum_required(VERSION 3.19)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug build")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")

elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Release build - optimized for size")
    set(CMAKE_CXX_FLAGS_RELEASE "-Os -flto -fPIC -fdata-sections -ffunction-sections -fno-exceptions  -Wl,--gc-sections -flto")

else() # ESP32 build
    add_definitions(-DESP32)
    include($ENV{IDF_PATH}/tools/cmake/project.cmake)
endif()

project(flappy VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(main/core/source platform)

if(PLATFORM STREQUAL "Desktop")
    add_definitions(-DDESKTOP)

    # link_directories(${CMAKE_SOURCE_DIR}/lib)
    include(_cmake/CPM.cmake)
    CPMAddPackage("gh:raysan5/raylib#5.0")

    add_library(core STATIC
    # core/source/multiplayer/network.cpp
    # core/source/multiplayer/pubsub.cpp
    main/core/source/scenario/scenario.cpp
    main/core/source/game/game.cpp
    main/core/source/pipe/pipe.cpp
    main/core/source/player/player.cpp
    main/core/source/score/score.cpp
    main/core/source/sprite/sprite.cpp)
    
    add_executable(flappy 
        main/main.cpp
        platform/interface/renderer.cpp
        platform/interface/inputer.cpp)

    # set(THREADS_PREFER_PTHREAD_FLAG ON)
    # find_package(Threads REQUIRED)

    target_link_libraries(flappy PRIVATE core raylib)
    target_compile_options(flappy PRIVATE -Wall -Wextra -Wpedantic -Werror)

else()
    # Add ESP32 specific configurations
    # include_directories(${ESP32_INCLUDE_DIR})
    # target_link_libraries(flappyTemplate ${ESP32_LIBRARIES})
endif()
