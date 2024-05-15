/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Shader
*/

#pragma once

// Engine include
#include "Error.hpp"
#include "Maths/Vector2.hpp"
#include "Maths/Vector3.hpp"
#include "Maths/Vector4.hpp"
#include "OpenGL.hpp"

// C++ include
#include <fstream>
#include <sstream>
#include <string>

namespace EGE {
    class Shader {
        public:
            class ShaderError : public Error {
                public:
                    ShaderError(const std::string &message) : Error(message) {}
            };

            /**
             * @brief Construct a new Shader object
             * This constructor will create a default shader and then call the compile method.
             *
             * @throw ShaderError if the shader compilation or linking failed.
             */
            Shader();

            /**
             * @brief Construct a new Shader object
             * This constructor will call the compile method with the content of the files.
             *
             * @param vertexPath Path to the vertex shader file
             * @param fragmentPath Path to the fragment shader file
             * @throw ShaderError if the shader compilation or linking failed.
            */
            Shader(const std::string &vertexPath, const std::string &fragmentPath);
            ~Shader();


            /**
             * @brief Use the shader
             * This method will call glUseProgram with the shader ID.
             *
             * @note This method should be called before drawing anything.
            */
            void use();

            /**
             * @brief Get the ID of the shader
             *
             * @return unsigned int The ID of the shader
            */
            unsigned int getID() const;

            /**
             * @brief Set a bool uniform value in the shader
             *
             * @param name The name of the uniform
             * @param value The value of the uniform
            */
            void setBool(const std::string &name, bool value) const;

            /**
             * @brief Set a double uniform value in the shader
             *
             * @param name The name of the uniform
             * @param value The value of the uniform
            */
            void setDouble(const std::string &name, double value) const;

            /**
             * @brief Set a float uniform value in the shader
             *
             * @param name The name of the uniform
             * @param value The value of the uniform
            */
            void setFloat(const std::string &name, float value) const;

            /**
             * @brief Set a signed int uniform value in the shader
             *
             * @param name The name of the uniform
             * @param value The value of the uniform
            */
            void setInt(const std::string &name, int value) const;

            /**
             * @brief Set a unsigned int uniform value in the shader
             *
             * @param name The name of the uniform
             * @param value The value of the uniform
            */
            void setUInt(const std::string &name, unsigned int value) const;

            /**
             * @brief Set a vec2 uniform value in the shader
             *
             * @param name The name of the uniform
             * @param value The value of the uniform
            */
            template<typename T>
            void setVec2(const std::string &name, const EGE::Maths::Vector2<T> &value) const;

            /**
             * @brief Set a vec3 uniform value in the shader
             *
             * @param name The name of the uniform
             * @param value The value of the uniform
            */
            template<typename T>
            void setVec3(const std::string &name, const EGE::Maths::Vector3<T> &value) const;

            /**
             * @brief Set a vec4 uniform value in the shader
             *
             * @param name The name of the uniform
             * @param value The value of the uniform
            */
            template<typename T>
            void setVec4(const std::string &name, const EGE::Maths::Vector4<T> &value) const;

            // TODO: Add matrix uniforms when the matrix class will be implemented

        private:

            /**
             * @brief Compile the shader
             *
             * @param vertexSource The source code of the vertex shader
             * @param fragmentSource The source code of the fragment shader
             * @throw ShaderError if the shader compilation or linking failed.
            */
            void compile(const std::string &vertexSource, const std::string &fragmentSource);

            unsigned int _ID;           ///< The ID of the shader program
            unsigned int _vertex;       ///< The ID of the vertex shader
            unsigned int _fragment;     ///< The ID of the fragment shader
    };
}