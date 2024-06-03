/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Slider
*/

#include "GUI/Input/Slider.hpp"

EGE::Slider::Slider(const std::string &title, float min, float max)
{
    this->_name = title;
    this->_min = min;
    this->_max = max;
    this->_value = 0.0;
    this->_callback = []() {};
    this->_visible = true;
}

EGE::Slider::~Slider()
{
}

void EGE::Slider::draw()
{
    if (!this->isVisible())
        return;
    ImGui::SliderFloat(this->_name.c_str(), &this->_value, this->_min, this->_max);
}

void EGE::Slider::setValue(float value)
{
    this->_value = value;
}

float EGE::Slider::getValue() const
{
    return this->_value;
}
