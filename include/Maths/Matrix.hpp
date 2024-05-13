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

template<int WIDTH, int HEIGHT>
class Matrix {
    public:
        class MatrixError : public Error {
            public:
                MatrixError(std::string const &message)
                    : Error(message) {};
        };

        Matrix()
        {
            for (int i = 0; i < HEIGHT; i++) {
                for (int j = 0; j < WIDTH; j++) {
                    _matrix[i][j] = 0.0;
                }
            }
        }

        Matrix(std::array<std::array<double, WIDTH>, HEIGHT> matrix)
        {
            _matrix = matrix;
        }

        ~Matrix() = default;

        double operator[](std::pair<int, int> pos) const
        {
            return _matrix[pos.first][pos.second];
        }

        double& operator[](std::pair<int, int> pos)
        {
            return _matrix[pos.first][pos.second];
        }

    private:
        std::array<std::array<double, WIDTH>, HEIGHT> _matrix;
};
