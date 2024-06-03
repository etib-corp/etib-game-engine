/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** ColorEditor
*/

#ifndef COLOREDITOR_HPP_
#define COLOREDITOR_HPP_

#include "GUI/Interactable.hpp"


namespace EGE {

    /**
     * @brief The ColorEditor class represents an interactable color editor.
     * 
     * This class allows the user to interactively edit and retrieve color values.
     */
    class ColorEditor : public Interactable {
        public:
            /**
             * @brief Constructs a ColorEditor object with an optional title.
             * 
             * @param title The title of the color editor.
             */
            ColorEditor(const std::string &title = "");
            
            /**
             * @brief Destroys the ColorEditor object.
             */
            ~ColorEditor();

            /**
             * @brief Draws the color editor.
             * 
             * This function is called to draw the color editor on the screen.
             */
            void draw() override;

            /**
             * @brief Sets the color of the editor.
             * 
             * @param red The red component of the color (0.0 - 1.0).
             * @param green The green component of the color (0.0 - 1.0).
             * @param blue The blue component of the color (0.0 - 1.0).
             * @param alpha The alpha component of the color (0.0 - 1.0). Default is 1.0.
             */
            void setColor(float red, float green, float blue, float alpha = 1.0);

            /**
             * @brief Returns the red component of the color.
             * 
             * @return The red component of the color (0.0 - 1.0).
             */
            float getRed() const;

            /**
             * @brief Returns the green component of the color.
             * 
             * @return The green component of the color (0.0 - 1.0).
             */
            float getGreen() const;

            /**
             * @brief Returns the blue component of the color.
             * 
             * @return The blue component of the color (0.0 - 1.0).
             */
            float getBlue() const;

            /**
             * @brief Returns the alpha component of the color.
             * 
             * @return The alpha component of the color (0.0 - 1.0).
             */
            float getAlpha() const;

            /**
             * @brief Returns a pointer to the color array.
             * 
             * @return A pointer to the color array.
             */
            float *getColor() const;
        protected:
            float _red; /**< The red component of the color. */
            float _green; /**< The green component of the color. */
            float _blue; /**< The blue component of the color. */
            float _alpha; /**< The alpha component of the color. */
    };
}

#endif /* !COLOR_HPP_ */
