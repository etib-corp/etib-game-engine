/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Slider
*/

#ifndef SLIDER_HPP_
#define SLIDER_HPP_

#include "GUI/Interactable.hpp"

namespace EGE {

    /**
     * @brief Represents a slider control that allows users to select a value within a specified range.
     */
    class Slider : public Interactable {
        public:
            /**
             * @brief Constructs a Slider object with the specified title, minimum value, and maximum value.
             * @param title The title of the slider.
             * @param min The minimum value of the slider.
             * @param max The maximum value of the slider.
             */
            Slider(const std::string &title = "", float min = 0.0, float max = 1.0);
            
            /**
             * @brief Destroys the Slider object.
             */
            ~Slider();

            /**
             * @brief Draws the slider control.
             */
            void draw() override;

            /**
             * @brief Sets the value of the slider.
             * @param value The value to set.
             */
            void setValue(float value);
            
            /**
             * @brief Gets the current value of the slider.
             * @return The current value of the slider.
             */
            float getValue() const;

        protected:
            float _min; /**< The minimum value of the slider. */
            float _max; /**< The maximum value of the slider. */
            float _value; /**< The current value of the slider. */
    };
}
#endif /* !SLIDER_HPP_ */
