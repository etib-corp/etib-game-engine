/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include "GUI/Container.hpp"
#include "GUI/Menu/Item.hpp"

namespace EGE {
    class Menu : public Container<Item> {
        public:
            Menu(const std::string &title);
            ~Menu();

            void draw() override;
    };
}

#endif /* !MENU_HPP_ */
