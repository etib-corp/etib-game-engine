/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Bar
*/

#ifndef BAR_HPP_
#define BAR_HPP_

#include "GUI/Container.hpp"
#include "GUI/Menu/Item.hpp"
#include "GUI/Menu/Menu.hpp"

namespace EGE {
    class Bar : public Container<Menu> {
        public:
            Bar();
            ~Bar();

            void hideBar();
            void showBar();
    };
}

#endif /* !MENUBAR_HPP_ */
