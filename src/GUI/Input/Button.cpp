/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Button
*/

#include "GUI/Input/Button.hpp"

EGE::Button::Button(const std::string &title, std::function<void()> callback)
{
    this->_name = title;
    this->_callback = callback;
}

EGE::Button::~Button()
{
}

void EGE::Button::draw()
{
    if (!this->isVisible())
        return;
    if (ImGui::Button(this->_name.c_str()))
        this->_callback();
}
