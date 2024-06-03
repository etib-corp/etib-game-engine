/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** RadioButton
*/

#ifndef RADIOBUTTON_HPP_
#define RADIOBUTTON_HPP_

#include "GUI/Input/Button.hpp"

namespace EGE {

    /**
     * @brief Represents a radio button GUI element.
     * 
     * The RadioButton class is a subclass of Button and represents a radio button GUI element.
     * It allows the user to select a single option from a group of options.
     */
    class RadioButton : public Button {
        public:
            /**
             * @brief Constructs a RadioButton object with the specified title.
             * 
             * @param title The title of the radio button.
             */
            RadioButton(const std::string &title);
            
            /**
             * @brief Destroys the RadioButton object.
             */
            ~RadioButton();

            /**
             * @brief Draws the radio button on the screen.
             * 
             * This function overrides the draw() function of the Button class.
             * It is responsible for rendering the radio button on the screen.
             */
            void draw() override;

            /**
             * @brief Sets the checked state of the radio button.
             * 
             * @param checked The checked state to set.
             */
            void setChecked(bool checked);
            
            /**
             * @brief Checks if the radio button is currently checked.
             * 
             * @return true if the radio button is checked, false otherwise.
             */
            bool isChecked() const;

        protected:
            bool _checked; /**< The checked state of the radio button. */
    };
}

#endif /* !RADIOBUTTON_HPP_ */
