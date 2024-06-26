/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Bar
*/

#include "GUI/Menu/Bar.hpp"

EGE::Bar::Bar()
{
    this->_visible = true;
}

EGE::Bar::~Bar()
{
}

void EGE::Bar::draw()
{
    if (!this->isVisible())
        return;
    if (ImGui::BeginMenuBar()) {
        for (auto &[name, menu] : this->_elements) {
            menu->draw();
        }
        ImGui::EndMenuBar();
    }
}

void EGE::Bar::hideBar()
{
    this->setVisible(false);
}

void EGE::Bar::showBar()
{
    this->setVisible(true);
}
