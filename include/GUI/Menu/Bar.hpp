/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Bar
*/

#ifndef BAR_HPP_
#define BAR_HPP_

#include "GUI/Container.hpp"
#include "GUI/Menu/Item.hpp"
#include "GUI/Menu/Menu.hpp"

namespace EGE {

    /**
     * @brief The Bar class represents a menu bar in the GUI.
     * 
     * It is a container that holds a collection of menu items.
     * The Bar class inherits from the Container class and is specialized for menus.
     */
    class Bar : public Container<Menu> {
        public:
            /**
             * @brief Constructs a Bar object.
             */
            Bar();
            
            /**
             * @brief Destroys the Bar object.
             */
            ~Bar();

            /**
             * @brief Draws the menu bar on the screen.
             * 
             * This function is called to render the menu bar on the GUI.
             * It overrides the draw() function from the base class.
             */
            void draw() override;

            /**
             * @brief Hides the menu bar.
             * 
             * This function hides the menu bar from the GUI.
             */
            void hideBar();

            /**
             * @brief Shows the menu bar.
             * 
             * This function shows the menu bar on the GUI.
             */
            void showBar();
    };
}

#endif /* !MENUBAR_HPP_ */
