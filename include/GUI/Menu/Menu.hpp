/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include "GUI/Container.hpp"
#include "GUI/Menu/Item.hpp"

namespace EGE {

    /**
     * @brief Represents a menu in the GUI.
     *
     * This class is a derived class of the Container class and represents a menu in the graphical user interface (GUI).
     * It provides functionality to draw the menu.
     */
    class Menu : public Container<Item> {
        public:
            /**
             * @brief Constructs a Menu object with the specified title.
             *
             * @param title The title of the menu.
             */
            Menu(const std::string &title);

            /**
             * @brief Destroys the Menu object.
             */
            ~Menu();

            /**
             * @brief Draws the menu.
             *
             * This function overrides the draw() function of the base class and is responsible for drawing the menu on the screen.
             */
            void draw() override;
    };
}

#endif /* !MENU_HPP_ */
