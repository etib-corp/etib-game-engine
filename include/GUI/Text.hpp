/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Text
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_

#include "GUI/GUI.hpp"

/**
    * @brief The EGE namespace contains classes and functions related to the ETIB Game Engine.
    */
namespace EGE {

    /**
     * @brief The Text class represents a GUI element for displaying text.
     */
    class Text : public GUI {
        public:
            /**
             * @brief Constructs a Text object with the given content.
             * @param content The text content to be displayed.
             */
            Text(const std::string &content);

            /**
             * @brief Destroys the Text object.
             */
            ~Text();

            /**
             * @brief Draws the Text element on the screen.
             */
            void draw() override;

    };
}

#endif /* !TEXT_HPP_ */
