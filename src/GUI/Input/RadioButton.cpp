/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** RadioButton
*/

#include "GUI/Input/RadioButton.hpp"

EGE::RadioButton::RadioButton(const std::string &title) : Button(title, []() {})
{
    this->_checked = false;
    this->_callback = []() {};
}

EGE::RadioButton::~RadioButton()
{
}

void EGE::RadioButton::draw()
{
    if (!this->isVisible())
        return;
    ImGui::RadioButton(this->_name.c_str(), this->_checked);
}

void EGE::RadioButton::setChecked(bool checked)
{
    this->_checked = checked;
}

bool EGE::RadioButton::isChecked() const
{
    return this->_checked;
}
