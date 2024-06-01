/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Item
*/

#ifndef ITEM_HPP_
#define ITEM_HPP_

#include "GUI/Interactable.hpp"

namespace EGE {
    class Item : public Interactable {
        public:
            Item(const std::string &title, std::function<void()> callback = nullptr);
            ~Item();

            void draw() override;
    };
}

#endif /* !ITEM_HPP_ */
