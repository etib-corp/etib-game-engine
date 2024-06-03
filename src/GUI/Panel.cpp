/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Panel
*/

#include "GUI/Panel.hpp"

EGE::Panel::Panel(const std::string &title)
{
    this->_name = title;
}

EGE::Panel::~Panel()
{
}

void EGE::Panel::draw()
{
    if (!this->isVisible())
        return;
    if (ImGui::Begin(this->_name.c_str())) {
        for (auto &item : this->_elements) {
            item->draw();
            ImGui::Spacing();
        }
        ImGui::End();
    }
}
