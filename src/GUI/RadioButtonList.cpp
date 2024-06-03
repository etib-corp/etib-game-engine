/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** RadioButtonList
*/

#include "GUI/RadioButtonList.hpp"

EGE::RadioButtonList::RadioButtonList()
{
    this->_lastChecked = 0;
}

EGE::RadioButtonList::~RadioButtonList()
{
}

void EGE::RadioButtonList::draw()
{
    if (!this->isVisible())
        return;

    int index = 0;

    for (auto &radioButton : this->_elements) {
        if (radioButton->isChecked()) {
            if (this->_elements[this->_lastChecked]->isChecked()) {
                this->_elements[this->_lastChecked]->setChecked(false);
            }
            this->_lastChecked = index;
        }
        radioButton->draw();
        index++;
    }
    this->_elements[index]->setChecked(true);
}