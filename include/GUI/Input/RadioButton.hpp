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
    class RadioButton : public Button {
        public:
            RadioButton(const std::string &title);
            ~RadioButton();

            void draw() override;

            void setChecked(bool checked);
            bool isChecked() const;

        protected:
            bool _checked;
    };
}

#endif /* !RADIOBUTTON_HPP_ */
