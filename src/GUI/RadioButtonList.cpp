/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** RadioButtonList
*/

#include "GUI/RadioButtonList.hpp"

EGE::RadioButtonList::RadioButtonList()
{
    // key of the fisrt element
    this->_lastChecked = this->_elements.begin()->first;
    this->_visible = true;
}

EGE::RadioButtonList::~RadioButtonList()
{
}

void EGE::RadioButtonList::draw()
{
    if (!this->isVisible())
        return;

    std::string current = this->_elements.begin()->first;

    for (auto &[name, radioButton] : this->_elements) {
        if (radioButton->isChecked()) {
            if (this->_elements[this->_lastChecked]->isChecked()) {
                this->_elements[this->_lastChecked]->setChecked(false);
            }
            this->_lastChecked = name;
        }
        radioButton->draw();
        current = name;
    }
    this->_elements[current]->setChecked(true);
}
