/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Item
*/

#include "GUI/Menu/Item.hpp"

EGE::Item::Item(const std::string &title, std::function<void()> callback)
{
    this->_name = title;
    this->_callback = callback;
    this->_visible = true;
}

EGE::Item::~Item()
{
}

void EGE::Item::draw()
{
    if (!this->isVisible())
        return;
    if (ImGui::MenuItem(this->_name.c_str()))
        this->_callback();
}
