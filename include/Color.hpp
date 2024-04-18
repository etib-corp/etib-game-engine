/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Color
*/

#pragma once

/**
 * @file Color.hpp
 * @brief Defines the Color class for representing RGBA colors.
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
     * @class Color
     * @brief Represents an RGBA color.
     *
     * The Color class provides a convenient way to represent colors in RGBA format.
     * Each color component (red, green, blue, alpha) is represented by an unsigned char
     * value ranging from 0.0f to 1.0f.
     */
    class Color {
        public:
            /**
             * @brief Constructs a Color object with the specified RGBA values.
             *
             * @param red The red component of the color (0.0f-1.0f).
             * @param green The green component of the color (0.0f-1.0f).
             * @param blue The blue component of the color (0.0f-1.0f).
             * @param alpha The alpha component of the color (0.0f-1.0f). Defaults to 1.0f (fully opaque).
             */
            Color(float red, float green, float blue, float alpha = 1.0f);

            /**
             * @brief Destructor for the Color class.
             *
             * This destructor is responsible for cleaning up any resources
             * allocated by the Color class.
             */
            ~Color();

            float red;   /**< The red component of the color (0.0f-1.0f). */
            float green; /**< The green component of the color (0.0f-1.0f). */
            float blue;  /**< The blue component of the color (0.0f-1.0f). */
            float alpha; /**< The alpha component of the color (0.0f-1.0f). */
    };
}