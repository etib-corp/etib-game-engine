cmake_minimum_required(VERSION 3.2)

project(EGE)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Populate(imgui
  URL https://github.com/ocornut/imgui/archive/docking.zip
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui
)

set(OpenGL_GL_PREFERENCE "LEGACY")
find_package(OpenGL 2 REQUIRED)
find_package(glfw3 REQUIRED)

add_library(imgui_glfw SHARED
  imgui/imgui.cpp
  imgui/imgui_draw.cpp
  imgui/imgui_demo.cpp
  imgui/imgui_tables.cpp
  imgui/imgui_widgets.cpp

  imgui/backends/imgui_impl_glfw.cpp
  imgui/backends/imgui_impl_opengl3.cpp
)

target_link_libraries(imgui_glfw PUBLIC glfw ${OPENGL_LIBRARIES})

target_include_directories(imgui_glfw
PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/imgui
  ${CMAKE_CURRENT_LIST_DIR}/imgui/backends
)

find_package(PkgConfig REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)

find_package(assimp REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-g3 -ggdb)
    message("Debug mode enabled")
endif()

include_directories(${GLFW_INCLUDE_DIRS} "include" "imgui")

add_library(EGE SHARED ${SOURCES})
set(GL_LIBS
    "GL"
    "glfw"
)
target_link_libraries(EGE PUBLIC ${GL_LIBS})

target_link_libraries(EGE PUBLIC assimp::assimp)

target_link_libraries(EGE PRIVATE imgui_glfw)

set_target_properties(EGE PROPERTIES OUTPUT_NAME "EGE-OpenGL")
set_target_properties(EGE PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")


if (NOT CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Building tests")
    file(GLOB_RECURSE TEST_SOURCES "tests/functional/src/*.cpp")

    include_directories("tests/functional/include")

    add_executable(EGE-Test ${TEST_SOURCES})

    target_link_libraries(EGE-Test EGE)

    set_target_properties(EGE-Test PROPERTIES OUTPUT_NAME "example")

    set_target_properties(EGE-Test PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../")
endif()
