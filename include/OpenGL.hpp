/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** OpenGL
*/

#pragma once

#define GL_GLEXT_PROTOTYPES

#ifdef VR
    #include <EGL/egl.h>
    #include <GLES3/gl3.h>
#endif

#include "glm.hpp"

#ifndef VR
    #include <GL/gl.h>
    #include <GLFW/glfw3.h>
#endif
