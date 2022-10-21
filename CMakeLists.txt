cmake_minimum_required(VERSION 3.23)
project(gameEngineV2)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)
include_directories(include)


link_directories("/usr/local/Cellar/llvm/15.0.0/lib/c++")
include_directories("/usr/local/Cellar/llvm/15.0.0/include/c++/v1")


find_package(glfw3 REQUIRED)
add_subdirectory(include/glm)

add_subdirectory(lib/FastNoise2)

file(GLOB SRC_FILES CONFIGURE_DEPENDS
        "src/*.cpp"
        "src/*.h"

        "src/*/*.cpp"
        "src/*/*.h"

        "src/graphics/opengl/*.cpp"
        "src/graphics/opengl/*.h"

        "src/glad.c")

add_executable(gameEngineV2 ${SRC_FILES})
target_link_libraries(gameEngineV2 glfw FastNoise2)

