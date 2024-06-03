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

    /**
     * @brief Represents a panel in the GUI.
     * 
     * This class inherits from the Container class and provides functionality for creating a panel in the GUI.
     */
    class Panel : public Container<GUI> {
        public:
            /**
             * @brief Constructs a Panel object with the specified title.
             * 
             * @param title The title of the panel.
             */
            Panel(const std::string &title);

            /**
             * @brief Destroys the Panel object.
             */
            ~Panel();

            /**
             * @brief Draws the panel on the screen.
             * 
             * This function overrides the draw() function of the base class.
             */
            void draw() override;

    };
}

#endif /* !PANEL_HPP_ */
