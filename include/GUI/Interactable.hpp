/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Interactable
*/

#ifndef INTERACTABLE_HPP_
#define INTERACTABLE_HPP_

#include "GUI/GUI.hpp"

#include <functional>

namespace EGE {
    class Interactable : public GUI {
        public:
            virtual ~Interactable() = default;

            void perform();

            void setCallback(std::function<void()> callback);

        protected:
            std::function<void()> _callback;

    };
}

#endif /* !INTERACTABLE_HPP_ */
