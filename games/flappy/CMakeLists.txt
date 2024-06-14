cmake_minimum_required(VERSION 3.19)

project(engine VERSION 0.1.0 LANGUAGES C CXX ASM)

add_definitions(-DDESKTOP)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(engine)

include_directories(../../platform ../../core ../../engine)

target_sources(engine PRIVATE main.cpp
    ../../engine/core/engine.cpp
    ../../core/interface/renderer.cpp
    ../../core/interface/inputer.cpp
    # core/engine.cpp
    # core/engine.cpp
    )

include(../../_cmake/CPM.cmake)
CPMAddPackage("gh:raysan5/raylib#5.0")
target_link_libraries(engine PRIVATE raylib)

# target_link_libraries(engine PRIVATE )

