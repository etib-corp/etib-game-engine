/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Button
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include "GUI/Interactable.hpp"

namespace EGE {
    class Button : public Interactable {
        public:
            Button(const std::string &title, std::function<void(void *)> callback);
            ~Button();

            void draw() override;

    };
}

#endif /* !BUTTON_HPP_ */
