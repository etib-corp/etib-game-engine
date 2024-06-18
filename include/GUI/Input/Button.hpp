/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Button
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include "GUI/Interactable.hpp"

namespace EGE {

    /**
     * @brief Represents a button that can be interacted with.
     */
    class Button : public Interactable {
        public:
            /**
             * @brief Constructs a Button object with the specified title and callback function.
             *
             * @param title The title of the button.
             * @param callback The callback function to be executed when the button is clicked.
             */
            Button(const std::string &title, std::function<void()> callback);

            /**
             * @brief Destroys the Button object.
             */
            ~Button();

            /**
             * @brief Draws the button on the screen.
             */
            void draw() override;

    };
}

#endif /* !BUTTON_HPP_ */
