/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Main
*/

#ifndef MAIN_HPP_
#define MAIN_HPP_

#include "GUI/Menu/Bar.hpp"

namespace EGE {

    /**
     * @brief The Main class represents the main menu of the game.
     *
     * This class inherits from the Bar class and provides functionality
     * to draw the main menu.
     */
    class Main : public Bar {
        public:
            /**
             * @brief Constructs a Main object.
             */
            Main();

            /**
             * @brief Destroys the Main object.
             */
            ~Main();

            /**
             * @brief Draws the main menu.
             *
             * This function overrides the draw() function of the Bar class
             * and is responsible for drawing the main menu on the screen.
             */
            void draw() override;

    };
}

#endif /* !MAIN_HPP_ */
