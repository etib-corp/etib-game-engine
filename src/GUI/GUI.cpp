/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** GUI
*/

#include "GUI/GUI.hpp"

std::string EGE::GUI::getName() const
{
    return this->_name;
}
void EGE::GUI::setName(std::string name)
{
    this->_name = name;
}

void EGE::GUI::setWindow(EGE::Window *window)
{
    this->_window = window;
}

EGE::Window *EGE::GUI::getWindow() const
{
    return this->_window;
}

void EGE::GUI::setVisible(bool visible)
{
    this->_visible = visible;
}

bool EGE::GUI::isVisible() const
{
    return this->_visible;
}

void EGE::GUI::init(Window *window)
{
    this->_window = window;
}

