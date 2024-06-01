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
    class Slider : public Interactable {
        public:
            Slider(const std::string &title = "", float min = 0.0, float max = 1.0);
            ~Slider();

            void draw() override;

            void setValue(float value);
            float getValue() const;

        protected:
            float _min;
            float _max;
            float _value;
    };
}
#endif /* !SLIDER_HPP_ */
