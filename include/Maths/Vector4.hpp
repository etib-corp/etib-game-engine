/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Vector4
*/

#pragma once


/**
 * @file Vector4.hpp
 * @brief Defines the Vector4 class for representing 4D vectors.
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
         * @brief A 4D vector class template.
         *
         * This class represents a 4D vector with x, y, z and w components.
         * The template parameter T represents the type of the vector components.
         */
        template <typename T>
        class Vector4 {
            public:
                /**
                 * @brief Constructs a Vector4 object with specified x, y, z and w components.
                 *
                 * @param x The x component of the vector.
                 * @param y The y component of the vector.
                 * @param z The z component of the vector.
                 * @param w The w component of the vector.
                 */
                Vector4(const T& x, const T& y, const T& z, const T& w) : x(x), y(y), z(z), w(w) {}

                /**
                 * @brief Constructs a Vector4 object with default x, y, z and w components.
                 *
                 * The default x and y components are set to 0.
                 */
                Vector4() : x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0)), w(static_cast<T>(0)) {}

                /**
                 * @brief Destructor for the Vector4 object.
                 */
                ~Vector4() {}

                T x; /**< The x component of the vector. */
                T y; /**< The y component of the vector. */
                T z; /**< The z component of the vector. */
                T w; /**< The w component of the vector. */
        };
    }
}