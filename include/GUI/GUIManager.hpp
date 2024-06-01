/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** GUIManager
*/

#ifndef GUIMANAGER_HPP_
#define GUIMANAGER_HPP_

#include "GUI/Panel.hpp"
#include "GUI/Menu/Bar.hpp"

namespace EGE {
    class GUIManager {
        public:
            virtual ~GUIManager() = default;

            void draw();

            std::vector<Panel *> _panels;
            Bar *_menuBar;
    };
}

#endif /* !GUIMANAGER_HPP_ */
