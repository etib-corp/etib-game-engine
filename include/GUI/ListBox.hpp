/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** ListBox
*/

#ifndef LISTBOX_HPP_
#define LISTBOX_HPP_

#include "GUI/Container.hpp"

namespace EGE {

    /**
     * @brief ListBox class represents a GUI component that displays a list of items.
     *
     * ListBox is a subclass of Container<GUI> and provides functionality to draw and manage a list of items.
     */
    class ListBox : public Container<GUI> {
        public:
            /**
             * @brief Constructs a ListBox object with the specified title.
             *
             * @param title The title of the ListBox.
             */
            ListBox(const std::string &title);

            /**
             * @brief Destructor for the ListBox class.
             */
            ~ListBox();

            /**
             * @brief Draws the ListBox on the screen.
             *
             * This function overrides the draw() function of the base class Container<GUI>.
             */
            void draw() override;

    };
}

#endif /* !LISTBOX_HPP_ */
