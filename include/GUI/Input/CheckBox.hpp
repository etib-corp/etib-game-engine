/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** CheckBox
*/

#ifndef CHECKBOX_HPP_
#define CHECKBOX_HPP_

#include "GUI/Input/Button.hpp"

namespace EGE {

    /**
     * @brief A class representing a checkbox GUI element.
     * 
     * This class inherits from the Button class and provides functionality for a checkbox element.
     */
    class CheckBox : public Button {
        public:
            /**
             * @brief Constructs a CheckBox object with the specified title.
             * 
             * @param title The title of the checkbox.
             */
            CheckBox(const std::string &title);
            
            /**
             * @brief Destroys the CheckBox object.
             */
            ~CheckBox();

            /**
             * @brief Draws the checkbox on the screen.
             */
            void draw() override;

            /**
             * @brief Sets the checked state of the checkbox.
             * 
             * @param checked The checked state to set.
             */
            void setChecked(bool checked);
            
            /**
             * @brief Checks if the checkbox is currently checked.
             * 
             * @return true if the checkbox is checked, false otherwise.
             */
            bool isChecked() const;

        protected:
            bool _checked; /**< The checked state of the checkbox. */
    };
}

#endif /* !CHECKBOX_HPP_ */
