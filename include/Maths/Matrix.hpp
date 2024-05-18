/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Matrix
*/

#pragma once

// Engine include
#include "Error.hpp"

// C++ include
#include <array>

/**
 * @file Matrix.hpp
 * @brief Defines the Matrix class for representing 4D vectors.
 */

/**
    * @namespace EGE
    * @brief Namespace for the ETIB Game Engine.
    *
    * The EGE namespace contains all the classes, functions, and variables
    * related to the ETIB Game Engine.
    */
namespace EGE {
    namespace Maths {
        template<int WIDTH, int HEIGHT>
        class Matrix {
            public:
                /**
                 * @brief Represents an error that can occur in the Matrix class.
                 */
                class MatrixError : public Error {
                public:
                    /**
                     * @brief Constructs a MatrixError object with the specified error message.
                     * @param message The error message.
                     */
                    MatrixError(std::string const &message)
                        : Error(message) {};
                };

                /**
                 * @brief Constructs a Matrix object with all elements set to 0.
                 *
                 * The constructor initializes all elements of the matrix to 0.
                */
                Matrix()
                {
                    for (int i = 0; i < HEIGHT; i++) {
                        for (int j = 0; j < WIDTH; j++) {
                            _matrix[i][j] = 0.0;
                        }
                    }
                }

                /**
                 * @brief Constructs a Matrix object with the specified elements.
                 *
                 * The constructor initializes the matrix with the specified elements.
                 * @param matrix The elements to initialize the matrix with.
                */
                Matrix(std::array<std::array<double, WIDTH>, HEIGHT> matrix)
                {
                    _matrix = matrix;
                }

                /**
                 * @brief Destroys the Matrix object.
                */
                ~Matrix() = default;

                /**
                 * @brief Returns the element at the specified position.
                 *
                 * The function returns the element at the specified position.
                 * @param pos The position of the element.
                 * @return The element at the specified position.
                 * @throw MatrixError if the position is out of bounds.
                */
                double operator[](std::pair<int, int> pos) const
                {
                    if (pos.first < 0 || pos.first >= HEIGHT || pos.second < 0 || pos.second >= WIDTH) {
                        throw MatrixError("Position out of range");
                    }
                    return _matrix[pos.first][pos.second];
                }

                /**
                 * @brief Returns the element at the specified position.
                 *
                 * The function returns the element at the specified position.
                 * @param pos The position of the element.
                 * @return The element at the specified position.
                 * @throw MatrixError if the position is out of bounds.
                */
                double& operator[](std::pair<int, int> pos)
                {
                    if (pos.first < 0 || pos.first >= HEIGHT || pos.second < 0 || pos.second >= WIDTH) {
                        throw MatrixError("Position out of range");
                    }
                    return _matrix[pos.first][pos.second];
                }

            private:
                std::array<std::array<double, WIDTH>, HEIGHT> _matrix;      ///< The matrix.
        };
    }
}