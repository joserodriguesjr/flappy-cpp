cmake_minimum_required(VERSION 3.19)

project(engine VERSION 0.1.0 LANGUAGES C CXX ASM)

add_definitions(-DDESKTOP)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
file(GLOB_RECURSE SOURCES src/*.cpp include/*.hpp)

add_executable(engine)

include_directories(../../platform ../../core ../../engine include)

target_sources(engine PRIVATE 
    main.cpp
    ${SOURCES}
    
    ../../engine/core/engine.cpp
    ../../core/interface/renderer.cpp
    ../../core/interface/inputer.cpp
    )

include(../../_cmake/CPM.cmake)
CPMAddPackage("gh:raysan5/raylib#5.0")
target_link_libraries(engine PRIVATE raylib)

# target_link_libraries(engine PRIVATE )

