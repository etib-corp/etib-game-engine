/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** String
*/

#include "GUI/Input/String.hpp"

EGE::String::String(const std::string &title)
{
    this->_name = title;
    this->_content = "Text";
    this->_callback = []() {};
    this->_visible = true;
}

EGE::String::~String()
{
}

void EGE::String::draw()
{
    if (!this->isVisible())
        return;

    char *value = nullptr;

    ImGui::InputText(this->_name.c_str(), value, 50);
    this->_content = value;
}

void EGE::String::setContent(const std::string &content)
{
    this->_content = content;
}

std::string EGE::String::getContent() const
{
    return this->_content;
}
