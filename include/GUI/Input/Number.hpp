/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Number
*/

#ifndef NUMBER_HPP_
#define NUMBER_HPP_

#include "GUI/Interactable.hpp"

namespace EGE {

    /**
     * @brief The Number class represents an interactable GUI element for inputting numeric values.
     */
    class Number : public Interactable {
        public:
            /**
             * @brief Constructs a Number object with an optional title.
             * @param title The title of the Number object.
             */
            Number(const std::string &title = "");

            /**
             * @brief Destroys the Number object.
             */
            ~Number();

            /**
             * @brief Draws the Number object on the screen.
             */
            void draw() override;

            /**
             * @brief Sets the value of the Number object.
             * @param value The value to set.
             */
            void setValue(float value);

            /**
             * @brief Gets the value of the Number object.
             * @return The value of the Number object.
             */
            float getValue() const;

        protected:
            float _value; /**< The value of the Number object. */
    };
}

#endif /* !NUMBER_HPP_ */
