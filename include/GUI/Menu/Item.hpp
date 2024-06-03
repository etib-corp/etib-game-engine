/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Item
*/

#ifndef ITEM_HPP_
#define ITEM_HPP_

#include "GUI/Interactable.hpp"

namespace EGE {

    /**
     * @brief Represents an item in a menu.
     * 
     * This class inherits from the Interactable class and provides functionality for drawing an item in a menu.
     */
    class Item : public Interactable {
        public:
            /**
             * @brief Constructs an Item object with the specified title and callback function.
             * 
             * @param title The title of the item.
             * @param callback The callback function to be called when the item is interacted with. Defaults to nullptr.
             */
            Item(const std::string &title, std::function<void()> callback = nullptr);
            
            /**
             * @brief Destroys the Item object.
             */
            ~Item();

            /**
             * @brief Draws the item.
             * 
             * This function overrides the draw() function of the Interactable class.
             */
            void draw() override;
    };
}

#endif /* !ITEM_HPP_ */
