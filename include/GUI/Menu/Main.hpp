/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Main
*/

#ifndef MAIN_HPP_
#define MAIN_HPP_

#include "GUI/Menu/Bar.hpp"

namespace EGE {
    class Main : public Bar {
        public:
            Main();
            ~Main();

            void draw() override;

    };
}

#endif /* !MAIN_HPP_ */
