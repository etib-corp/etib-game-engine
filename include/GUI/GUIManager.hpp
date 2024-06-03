/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** GUIManager
*/

#ifndef GUIMANAGER_HPP_
#define GUIMANAGER_HPP_

#include "GUI/Panel.hpp"
#include "GUI/Menu/Main.hpp"

#include "GUI/Input/Button.hpp"
#include "GUI/Input/CheckBox.hpp"
#include "GUI/Input/ColorEditor.hpp"
#include "GUI/Input/Number.hpp"
#include "GUI/Input/Slider.hpp"
#include "GUI/Input/String.hpp"

#include "GUI/Text.hpp"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace EGE {
    class GUIManager {
        public:
            ~GUIManager();


            void init(Window *win);

            void clear();
            void draw();
            void display();

            std::vector<Panel *> _panels;
            Main *_menuBar;

            Window *_window;
    };
}

#endif /* !GUIMANAGER_HPP_ */
