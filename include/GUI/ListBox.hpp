/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** ListBox
*/

#ifndef LISTBOX_HPP_
#define LISTBOX_HPP_

#include "GUI/Container.hpp"

namespace EGE {
    class ListBox : public Container<GUI> {
        public:
            ListBox(const std::string &title);
            ~ListBox();

            void draw() override;

    };
}

#endif /* !LISTBOX_HPP_ */
