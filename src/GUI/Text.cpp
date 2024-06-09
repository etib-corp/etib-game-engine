/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Text
*/

#include "GUI/Text.hpp"

EGE::Text::Text(const std::string &content)
{
    this->_name = content;
    this->_visible = true;
}

EGE::Text::~Text()
{
}

void EGE::Text::draw()
{
    if (!this->isVisible())
        return;
    ImGui::Text("%s", this->_name.c_str());
}
