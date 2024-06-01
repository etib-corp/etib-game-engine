/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Container
*/

#ifndef CONTAINER_HPP_
#define CONTAINER_HPP_

#include "GUI/GUI.hpp"

namespace EGE {
    template<typename T>
    class Container : public GUI {
        public:
            virtual ~Container() = default;

            void add(T *gui);
            void remove(T *gui);

        protected:
            std::vector<T *> _elements;

    };
}

#endif /* !CONTAINER_HPP_ */
