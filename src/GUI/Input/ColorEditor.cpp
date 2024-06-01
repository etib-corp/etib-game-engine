/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Color
*/

#include "GUI/Input/ColorEditor.hpp"

EGE::ColorEditor::ColorEditor(const std::string &title)
{
    this->_name = title;
    this->_red = 0;
    this->_green = 0;
    this->_blue = 0;
    this->_alpha = 1;
    this->_callback = []() {};
}

EGE::ColorEditor::~ColorEditor()
{
}

void EGE::ColorEditor::draw()
{
    if (!this->isVisible())
        return;

    float color[4] = {this->_red, this->_green, this->_blue, this->_alpha};
    ImGui::ColorEdit4(this->_name.c_str(), color);
    this->_red = color[0];
    this->_green = color[1];
    this->_blue = color[2];
    this->_alpha = color[3];
}

void EGE::ColorEditor::setColor(float red, float green, float blue, float alpha)
{
    this->_red = red;
    this->_green = green;
    this->_blue = blue;
    this->_alpha = alpha;
}

float EGE::ColorEditor::getRed() const
{
    return this->_red;
}

float EGE::ColorEditor::getGreen() const
{
    return this->_green;
}

float EGE::ColorEditor::getBlue() const
{
    return this->_blue;
}

float EGE::ColorEditor::getAlpha() const
{
    return this->_alpha;
}

float *EGE::ColorEditor::getColor() const
{
    float *color = new float[4];
    color[0] = this->_red;
    color[1] = this->_green;
    color[2] = this->_blue;
    color[3] = this->_alpha;
    return color;
}
