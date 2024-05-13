/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Vector3
*/

#pragma once

/**
 * @file Vector3.hpp
 * @brief Defines the Vector3 class for representing 3D vectors.
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
         * @brief A 3D vector class template.
         *
         * This class represents a 3D vector with x, y, and z components.
         * The template parameter T represents the type of the vector components.
         */
        template <typename T>
        class Vector3 {
            public:
                /**
                 * @brief Constructs a Vector3 object with specified x, y and z components.
                 *
                 * @param x The x component of the vector.
                 * @param y The y component of the vector.
                 * @param z The z component of the vector.
                 */
                Vector3(const T& x, const T& y, const T& z) : x(x), y(y), z(z) {}

                /**
                 * @brief Constructs a Vector3 object with default x, y and z components.
                 *
                 * The default x, y and z components are set to 0.
                 */
                Vector3() : x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0)) {}

                /**
                 * @brief Destructor for the Vector3 object.
                 */
                ~Vector3() {}

                T x; /**< The x component of the vector. */
                T y; /**< The y component of the vector. */
                T z; /**< The z component of the vector. */
        };
    }
}