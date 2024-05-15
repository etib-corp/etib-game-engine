/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Shader
*/

#include "Shader.hpp"

EGE::Shader::Shader()
{
    std::string vertexShader = "#version 330 core\n"
                               "layout (location = 0) in vec3 aPos;\n"
                               "void main()\n"
                               "{\n"
                               "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                               "}\0";
    std::string fragmentShader = "#version 330 core\n"
                                 "out vec4 FragColor;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                 "}\0";
    this->compile(vertexShader, fragmentShader);
}

EGE::Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string vertexShaderSource;
    std::string fragmentShaderSource;
    std::ifstream vertexFile;
    std::ifstream fragmentFile;

    vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        vertexFile.open(vertexPath);
        fragmentFile.open(fragmentPath);
        std::stringstream vertexStream, fragmentStream;
        vertexStream << vertexFile.rdbuf();
        fragmentStream << fragmentFile.rdbuf();
        vertexFile.close();
        fragmentFile.close();
        vertexShaderSource = vertexStream.str();
        fragmentShaderSource = fragmentStream.str();
    } catch (std::ifstream::failure &e) {
        throw ShaderError("ERROR\n\tSHADER FILE CAN'T BE READ\n\t\t" + std::string(e.what()) + "\n");
    }
    this->compile(vertexShaderSource, fragmentShaderSource);
}

void EGE::Shader::compile(const std::string& vertexSource, const std::string& fragmentSource)
{
    const char *vertexShaderSource = NULL;
    const char *fragmentShaderSource = NULL;
    int succes = 0;
    char infoLog[512] = {0};

    this->_vertex = glCreateShader(GL_VERTEX_SHADER);
    vertexShaderSource = vertexSource.c_str();
    glShaderSource(this->_vertex, 1, &vertexShaderSource, NULL);
    glCompileShader(this->_vertex);
    glGetShaderiv(this->_vertex, GL_COMPILE_STATUS, &succes);
    if (!succes) {
        glGetShaderInfoLog(this->_vertex, 512, NULL, infoLog);
        throw ShaderError("ERROR\n\tVERTEX SHADER COMPILATION_FAILED\n\t\t" + std::string(infoLog));
    }

    this->_fragment = glCreateShader(GL_FRAGMENT_SHADER);
    fragmentShaderSource = fragmentSource.c_str();
    glShaderSource(this->_fragment, 1, &fragmentShaderSource, NULL);
    glCompileShader(this->_fragment);
    glGetShaderiv(this->_fragment, GL_COMPILE_STATUS, &succes);
    if (!succes) {
        glGetShaderInfoLog(this->_fragment, 512, NULL, infoLog);
        throw ShaderError("ERROR\n\tFRAGMENT SHADER COMPILATION_FAILED\n\t\t" + std::string(infoLog));
    }

    this->_ID = glCreateProgram();
    glAttachShader(this->_ID, this->_vertex);
    glAttachShader(this->_ID, this->_fragment);
    glLinkProgram(this->_ID);
    glGetProgramiv(this->_ID, GL_LINK_STATUS, &succes);
    if (!succes) {
        glGetProgramInfoLog(this->_ID, 512, NULL, infoLog);
        throw ShaderError("ERROR\n\tSHADER PROGRAM LINKING_FAILED\n\t\t" + std::string(infoLog));
    }
    glDeleteShader(this->_vertex);
    glDeleteShader(this->_fragment);
}

EGE::Shader::~Shader()
{
    glDeleteProgram(this->_ID);
}

void EGE::Shader::use()
{
    glUseProgram(this->_ID);
}

unsigned int EGE::Shader::getID() const
{
    return this->_ID;
}

void EGE::Shader::setBool(const std::string& name, bool value) const
{
    unsigned int location = glGetUniformLocation(this->_ID, name.c_str());

    if (location == -1)
        throw ShaderError("ERROR\n\tUNIFORM NOT FOUND\n\t\twhile trying to set " + name + " to " + std::to_string(value) + "\n");
    glUniform1i(location, (int)value);
}

void EGE::Shader::setDouble(const std::string& name, double value) const
{
    unsigned int location = glGetUniformLocation(this->_ID, name.c_str());

    if (location == -1)
        throw ShaderError("ERROR\n\tUNIFORM NOT FOUND\n\t\twhile trying to set " + name + " to " + std::to_string(value) + "\n");
    glUniform1d(location, value);
}

void EGE::Shader::setFloat(const std::string& name, float value) const
{
    unsigned int location = glGetUniformLocation(this->_ID, name.c_str());

    if (location == -1)
        throw ShaderError("ERROR\n\tUNIFORM NOT FOUND\n\t\twhile trying to set " + name + " to " + std::to_string(value) + "\n");
    glUniform1f(location, value);
}

void EGE::Shader::setInt(const std::string& name, int value) const
{
    unsigned int location = glGetUniformLocation(this->_ID, name.c_str());

    if (location == -1)
        throw ShaderError("ERROR\n\tUNIFORM NOT FOUND\n\t\twhile trying to set " + name + " to " + std::to_string(value) + "\n");
    glUniform1i(location, value);
}

void EGE::Shader::setUInt(const std::string& name, unsigned int value) const
{
    unsigned int location = glGetUniformLocation(this->_ID, name.c_str());

    if (location == -1)
        throw ShaderError("ERROR\n\tUNIFORM NOT FOUND\n\t\twhile trying to set " + name + " to " + std::to_string(value) + "\n");
    glUniform1ui(location, value);
}

template<>
void EGE::Shader::setVec2(const std::string& name, const EGE::Maths::Vector2<bool>& value) const
{
    unsigned int location = glGetUniformLocation(this->_ID, name.c_str());

    if (location == -1)
        throw ShaderError("ERROR\n\tUNIFORM NOT FOUND\n\t\twhile trying to set " + name + " to " + std::to_string(value.x) + ", " + std::to_string(value.y) + "\n");
    glUniform2i(location, (int)value.x, (int)value.y);
}

template<>
void EGE::Shader::setVec2(const std::string& name, const EGE::Maths::Vector2<double>& value) const
{
    unsigned int location = glGetUniformLocation(this->_ID, name.c_str());

    if (location == -1)
        throw ShaderError("ERROR\n\tUNIFORM NOT FOUND\n\t\twhile trying to set " + name + " to " + std::to_string(value.x) + ", " + std::to_string(value.y) + "\n");
    glUniform2d(location, value.x, value.y);
}

template<>
void EGE::Shader::setVec2(const std::string& name, const EGE::Maths::Vector2<float>& value) const
{
    unsigned int location = glGetUniformLocation(this->_ID, name.c_str());

    if (location == -1)
        throw ShaderError("ERROR\n\tUNIFORM NOT FOUND\n\t\twhile trying to set " + name + " to " + std::to_string(value.x) + ", " + std::to_string(value.y) + "\n");
    glUniform2f(location, value.x, value.y);
}

template<>
void EGE::Shader::setVec2(const std::string& name, const EGE::Maths::Vector2<int>& value) const
{
    unsigned int location = glGetUniformLocation(this->_ID, name.c_str());

    if (location == -1)
        throw ShaderError("ERROR\n\tUNIFORM NOT FOUND\n\t\twhile trying to set " + name + " to " + std::to_string(value.x) + ", " + std::to_string(value.y) + "\n");
    glUniform2i(location, value.x, value.y);
}

template<>
void EGE::Shader::setVec2(const std::string& name, const EGE::Maths::Vector2<unsigned int>& value) const
{
    unsigned int location = glGetUniformLocation(this->_ID, name.c_str());

    if (location == -1)
        throw ShaderError("ERROR\n\tUNIFORM NOT FOUND\n\t\twhile trying to set " + name + " to " + std::to_string(value.x) + ", " + std::to_string(value.y) + "\n");
    glUniform2ui(location, value.x, value.y);
}

template<>
void EGE::Shader::setVec3(const std::string& name, const EGE::Maths::Vector3<bool>& value) const
{
    unsigned int location = glGetUniformLocation(this->_ID, name.c_str());

    if (location == -1)
        throw ShaderError("ERROR\n\tUNIFORM NOT FOUND\n\t\twhile trying to set " + name + " to " + std::to_string(value.x) + ", " + std::to_string(value.y) + "\n");
    glUniform3i(location, (int)value.x, (int)value.y, value.z);
}

template<>
void EGE::Shader::setVec3(const std::string& name, const EGE::Maths::Vector3<double>& value) const
{
    unsigned int location = glGetUniformLocation(this->_ID, name.c_str());

    if (location == -1)
        throw ShaderError("ERROR\n\tUNIFORM NOT FOUND\n\t\twhile trying to set " + name + " to " + std::to_string(value.x) + ", " + std::to_string(value.y) + "\n");
    glUniform3d(location, value.x, value.y, value.z);
}

template<>
void EGE::Shader::setVec3(const std::string& name, const EGE::Maths::Vector3<float>& value) const
{
    unsigned int location = glGetUniformLocation(this->_ID, name.c_str());

    if (location == -1)
        throw ShaderError("ERROR\n\tUNIFORM NOT FOUND\n\t\twhile trying to set " + name + " to " + std::to_string(value.x) + ", " + std::to_string(value.y) + "\n");
    glUniform3f(location, value.x, value.y, value.z);
}

template<>
void EGE::Shader::setVec3(const std::string& name, const EGE::Maths::Vector3<int>& value) const
{
    unsigned int location = glGetUniformLocation(this->_ID, name.c_str());

    if (location == -1)
        throw ShaderError("ERROR\n\tUNIFORM NOT FOUND\n\t\twhile trying to set " + name + " to " + std::to_string(value.x) + ", " + std::to_string(value.y) + "\n");
    glUniform3i(location, value.x, value.y, value.z);
}

template<>
void EGE::Shader::setVec3(const std::string& name, const EGE::Maths::Vector3<unsigned int>& value) const
{
    unsigned int location = glGetUniformLocation(this->_ID, name.c_str());

    if (location == -1)
        throw ShaderError("ERROR\n\tUNIFORM NOT FOUND\n\t\twhile trying to set " + name + " to " + std::to_string(value.x) + ", " + std::to_string(value.y) + "\n");
    glUniform3ui(location, value.x, value.y, value.z);
}

template<>
void EGE::Shader::setVec4(const std::string& name, const EGE::Maths::Vector4<bool>& value) const
{
    unsigned int location = glGetUniformLocation(this->_ID, name.c_str());

    if (location == -1)
        throw ShaderError("ERROR\n\tUNIFORM NOT FOUND\n\t\twhile trying to set " + name + " to " + std::to_string(value.x) + ", " + std::to_string(value.y) + "\n");
    glUniform4i(location, (int)value.x, (int)value.y, value.z, value.w);
}

template<>
void EGE::Shader::setVec4(const std::string& name, const EGE::Maths::Vector4<double>& value) const
{
    unsigned int location = glGetUniformLocation(this->_ID, name.c_str());

    if (location == -1)
        throw ShaderError("ERROR\n\tUNIFORM NOT FOUND\n\t\twhile trying to set " + name + " to " + std::to_string(value.x) + ", " + std::to_string(value.y) + "\n");
    glUniform4d(location, value.x, value.y, value.z, value.w);
}

template<>
void EGE::Shader::setVec4(const std::string& name, const EGE::Maths::Vector4<float>& value) const
{
    unsigned int location = glGetUniformLocation(this->_ID, name.c_str());

    if (location == -1)
        throw ShaderError("ERROR\n\tUNIFORM NOT FOUND\n\t\twhile trying to set " + name + " to " + std::to_string(value.x) + ", " + std::to_string(value.y) + "\n");
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

template<>
void EGE::Shader::setVec4(const std::string& name, const EGE::Maths::Vector4<int>& value) const
{
    unsigned int location = glGetUniformLocation(this->_ID, name.c_str());

    if (location == -1)
        throw ShaderError("ERROR\n\tUNIFORM NOT FOUND\n\t\twhile trying to set " + name + " to " + std::to_string(value.x) + ", " + std::to_string(value.y) + "\n");
    glUniform4i(location, value.x, value.y, value.z, value.w);
}

template<>
void EGE::Shader::setVec4(const std::string& name, const EGE::Maths::Vector4<unsigned int>& value) const
{
    unsigned int location = glGetUniformLocation(this->_ID, name.c_str());

    if (location == -1)
        throw ShaderError("ERROR\n\tUNIFORM NOT FOUND\n\t\twhile trying to set " + name + " to " + std::to_string(value.x) + ", " + std::to_string(value.y) + "\n");
    glUniform4ui(location, value.x, value.y, value.z, value.w);
}
