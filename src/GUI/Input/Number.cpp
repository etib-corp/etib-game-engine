/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Number
*/

#include "GUI/Input/Number.hpp"

EGE::Number::Number(const std::string &title)
{
    this->_name = title;
    this->_value = 0.0;
    this->_callback = []() {};
    this->_visible = true;
}

EGE::Number::~Number()
{
}

void EGE::Number::draw()
{
    if (!this->isVisible())
        return;
    ImGui::InputFloat(this->_name.c_str(), &this->_value);
}

void EGE::Number::setValue(float value)
{
    this->_value = value;
}

float EGE::Number::getValue() const
{
    return this->_value;
}
