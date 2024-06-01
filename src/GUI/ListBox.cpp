/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** ListBox
*/

#include "GUI/ListBox.hpp"

EGE::ListBox::ListBox(const std::string &title)
{
    this->_name = title;
}

EGE::ListBox::~ListBox()
{
}

void EGE::ListBox::draw()
{
    if (!this->isVisible())
        return;
    if (ImGui::BeginListBox(this->_name.c_str())) {
        for (auto &item : this->_elements) {
            item->draw();
        }
        ImGui::EndListBox();
    }
}
