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
    class CheckBox : public Button {
        public:
            CheckBox(const std::string &title);
            ~CheckBox();

            void draw() override;

            void setChecked(bool checked);
            bool isChecked() const;

        protected:
            bool _checked;
    };
}

#endif /* !CHECKBOX_HPP_ */
