/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** CheckBox
*/

#include "GUI/Input/CheckBox.hpp"

EGE::CheckBox::CheckBox(const std::string &title) : Button(title, []() {})
{
    this->_checked = false;
    this->_callback = []() {};
}

EGE::CheckBox::~CheckBox()
{
}

void EGE::CheckBox::draw()
{
    if (!this->isVisible())
        return;
    ImGui::Checkbox(this->_name.c_str(), &this->_checked);
}

void EGE::CheckBox::setChecked(bool checked)
{
    this->_checked = checked;
}

bool EGE::CheckBox::isChecked() const
{
    return this->_checked;
}
