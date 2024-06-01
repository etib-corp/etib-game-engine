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
    class Number : public Interactable {
        public:
            Number(const std::string &title = "");
            ~Number();

            void draw() override;

            void setValue(float value);
            float getValue() const;

        protected:
            float _value;
    };
}

#endif /* !NUMBER_HPP_ */
