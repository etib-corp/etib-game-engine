/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** GUI
*/

#ifndef GUI_HPP_
#define GUI_HPP_

#include "Window.hpp"

#include <memory>

#include "imgui.h"

namespace EGE {
    class GUI {
        public:
            virtual ~GUI() = default;

            virtual void draw() = 0;

            void init(Window *window);

            std::string getName() const;
            void setName(std::string name);

            void setWindow(Window *window);
            Window *getWindow() const;

            void setVisible(bool visible);
            bool isVisible() const;

        protected:
            Window *_window;
            std::string _name;
            bool _visible;
    };
}

#endif /* !GUI_HPP_ */
