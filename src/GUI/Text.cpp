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
}

EGE::Text::~Text()
{
}

void EGE::Text::draw()
{
    if (!this->isVisible())
        return;
    ImGui::Text(this->_name.c_str());
}
