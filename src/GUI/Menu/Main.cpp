/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Main
*/

#include "GUI/Menu/Main.hpp"

EGE::Main::Main()
{
    this->_visible = true;
}

EGE::Main::~Main()
{
}

void EGE::Main::draw()
{
    if (!this->isVisible())
        return;
    if (ImGui::BeginMainMenuBar()) {
        for (auto &menu : this->_elements) {
            menu->draw();
        }
        ImGui::EndMainMenuBar();
    }
}
