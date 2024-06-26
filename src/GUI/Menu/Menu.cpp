/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Menu
*/

#include "GUI/Menu/Menu.hpp"

EGE::Menu::Menu(const std::string &title)
{
    this->_name = title;
    this->_visible = true;
}

EGE::Menu::~Menu()
{
}

void EGE::Menu::draw()
{
    if (!this->isVisible())
        return;
    if (ImGui::BeginMenu(this->_name.c_str())) {
        for (auto &[name, item] : this->_elements) {
            item->draw();
        }
        ImGui::EndMenu();
    }
}
