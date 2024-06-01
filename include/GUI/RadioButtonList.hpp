/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** RadioButtonList
*/

#ifndef RADIOBUTTONLIST_HPP_
#define RADIOBUTTONLIST_HPP_

#include "GUI/Input/RadioButton.hpp"
#include "GUI/Container.hpp"

namespace EGE {
    class RadioButtonList : public Container<RadioButton>{
        public:
            RadioButtonList();
            ~RadioButtonList();

            void draw() override;

        private:
            int _lastChecked;

    };
}

#endif /* !RADIOBUTTONLIST_HPP_ */
