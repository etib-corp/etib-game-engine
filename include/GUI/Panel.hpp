/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Panel
*/

#ifndef PANEL_HPP_
#define PANEL_HPP_

#include "GUI/Container.hpp"

namespace EGE {
    class Panel : public Container<GUI> {
        public:
            Panel(const std::string &title);
            ~Panel();

            void draw() override;

    };
}

#endif /* !PANEL_HPP_ */
