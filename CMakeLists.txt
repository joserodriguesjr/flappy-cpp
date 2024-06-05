cmake_minimum_required(VERSION 3.19)

# For clangd intellisense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(template VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug build")
    add_definitions(-DDEBUG_BUILD)
else()
    message(STATUS "Release build")
endif()

# Packages
include(_cmake/CPM.cmake)
CPMAddPackage("gh:gabime/spdlog@1.14.1")
CPMAddPackage("gh:catchorg/Catch2@3.6.0")

# Include directories
include_directories(core/source)

# App
add_executable(app app/source/app.cpp core/source/example/factorial.cpp)
target_link_libraries(app PRIVATE spdlog::spdlog)

# Testing
add_executable(core_tests tests/core/core_test.cpp core/source/example/factorial.cpp)
target_link_libraries(core_tests PRIVATE Catch2::Catch2WithMain)
# add_executable(app_tests tests/app/app_test.cpp)
