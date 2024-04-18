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
                Vector2(const T& x, const T& y) : _x(x), _y(y) {}

                /**
                 * @brief Constructs a Vector2 object with default x and y components.
                 *
                 * The default x and y components are set to 0.
                 */
                Vector2() : _x(static_cast<T>(0)), _y(static_cast<T>(0)) {}

                /**
                 * @brief Destructor for the Vector2 object.
                 */
                ~Vector2() {}

                /**
                 * @brief Sets the x component of the vector.
                 *
                 * @param x The new value for the x component.
                 */
                void setX(const T& x) { _x = x; }

                /**
                 * @brief Sets the y component of the vector.
                 *
                 * @param y The new value for the y component.
                 */
                void setY(const T& y) { _y = y; }

                /**
                 * @brief Gets the x component of the vector.
                 *
                 * @return The x component of the vector.
                 */
                T getX() const { return _x; }

                /**
                 * @brief Gets the y component of the vector.
                 *
                 * @return The y component of the vector.
                 */
                T getY() const { return _y; }

            private:
                T _x; /**< The x component of the vector. */
                T _y; /**< The y component of the vector. */
        };
    }
}
