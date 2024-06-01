/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** GUIManager
*/

#include "GUI/GUIManager.hpp"

void EGE::GUIManager::draw()
{
    this->_menuBar->draw();
    for (auto &gui : this->_panels) {
        gui->draw();
    }
}
