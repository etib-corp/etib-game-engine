/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Vector2
*/

#pragma once

/**
 * @file Vector2.hpp
 * @brief Defines the Vector2 class for representing 2D vectors.
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
        /**
         * @brief A 2D vector class template.
         *
         * This class represents a 2D vector with x and y components.
         * The template parameter T represents the type of the vector components.
         */
        template <typename T>
        class Vector2 {
            public:
                /**
                 * @brief Constructs a Vector2 object with specified x and y components.
                 *
                 * @param x The x component of the vector.
                 * @param y The y component of the vector.
                 */
                Vector2(const T& x, const T& y) : x(x), y(y) {}

                /**
                 * @brief Constructs a Vector2 object with default x and y components.
                 *
                 * The default x and y components are set to 0.
                 */
                Vector2() : x(static_cast<T>(0)), y(static_cast<T>(0)) {}

                /**
                 * @brief Destructor for the Vector2 object.
                 */
                ~Vector2() {}

                T x; /**< The x component of the vector. */
                T y; /**< The y component of the vector. */
        };
    }
}
