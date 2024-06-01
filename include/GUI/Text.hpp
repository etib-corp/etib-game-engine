/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Text
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_

#include "GUI/GUI.hpp"

namespace EGE {
    class Text : public GUI {
        public:
            Text(const std::string &content);
            ~Text();

            void draw() override;

    };
}

#endif /* !TEXT_HPP_ */
