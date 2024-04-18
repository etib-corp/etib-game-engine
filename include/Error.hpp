/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Error
*/

#pragma once

// C++ include
#include <exception>
#include <string>

/**
 * @file Error.hpp
 * @brief Defines the Error class for the ETIB Game Engine.
 */

/**
    * @namespace EGE
    * @brief Namespace for the ETIB Game Engine.
    *
    * The EGE namespace contains all the classes, functions, and variables
    * related to the ETIB Game Engine.
    */
namespace EGE {
    /**
     * @brief The Error class represents an exception that can be thrown in the EGE game engine.
     *
     * This class inherits from std::exception and provides a custom error message.
     */
    class Error : public std::exception {
    public:
        /**
         * @brief Constructs an Error object with the specified error message.
         *
         * @param message The error message.
         */
        Error(const std::string& message) : _message(message) {}

        /**
         * @brief Destructor for the Error object.
         */
        ~Error() {}

        /**
         * @brief Returns a C-style string representing the error message.
         *
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept override { return _message.c_str(); }
    protected:
        std::string _message; /**< The error message. */
    };
}
