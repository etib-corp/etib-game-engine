cmake_minimum_required(VERSION 3.2)

project(EGE)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)

find_package(assimp REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-g3 -ggdb)
    message("Debug mode enabled")
endif()

include_directories(${GLFW_INCLUDE_DIRS} "include")

add_library(EGE SHARED ${SOURCES})
set(GL_LIBS
    "GL"
    "glfw"
)
target_link_libraries(EGE PUBLIC ${GL_LIBS})

target_link_libraries(EGE PUBLIC assimp::assimp)

set_target_properties(EGE PROPERTIES OUTPUT_NAME "EGE-OpenGL")
set_target_properties(EGE PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug" AND CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    message("Building tests")
    file(GLOB_RECURSE TEST_SOURCES "tests/functional/src/*.cpp")

    include_directories("tests/functional/include")

    add_executable(EGE-Test ${TEST_SOURCES})

    target_link_libraries(EGE-Test EGE)

    set_target_properties(EGE-Test PROPERTIES OUTPUT_NAME "example")

    set_target_properties(EGE-Test PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../")
endif()
