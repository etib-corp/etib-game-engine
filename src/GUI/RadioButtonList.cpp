/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** RadioButtonList
*/

#include "GUI/RadioButtonList.hpp"

EGE::RadioButtonList::RadioButtonList()
{
    this->_lastChecked = "";
    this->_visible = true;
}

EGE::RadioButtonList::~RadioButtonList()
{
}

void EGE::RadioButtonList::draw()
{
    if (!this->isVisible())
        return;

    for (auto &[name, button] : this->_elements) {
        if (button->isChecked()) {
            if (this->_lastChecked == "") {
                this->_lastChecked = name;
            } else {
                if (this->_lastChecked != name) {
                    this->_elements[this->_lastChecked]->setChecked(false);
                    this->_lastChecked = name;
                }
            }
            this->_elements[this->_lastChecked]->setChecked(true);
        }
        button->draw();
    }
}
