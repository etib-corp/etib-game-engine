/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Interactable
*/

#ifndef INTERACTABLE_HPP_
#define INTERACTABLE_HPP_

#include "GUI/GUI.hpp"

#include <functional>

namespace EGE {

    /**
     * @brief The base class for interactable GUI elements.
     *
     * This class provides a common interface for GUI elements that can be interacted with, such as buttons.
     * It inherits from the GUI class.
     */
    class Interactable : public GUI {
        public:
            /**
             * @brief Destructor for the Interactable class.
             *
             * This is a virtual destructor to ensure proper cleanup when derived classes are destroyed.
             */
            virtual ~Interactable() = default;

            /**
             * @brief Perform the interaction action.
             *
             * This function is called when the interactable GUI element is interacted with.
             * Derived classes should override this function to define their specific interaction behavior.
             */
            void perform();

            /**
             * @brief Set the callback function for the interaction action.
             *
             * This function sets the callback function that will be called when the interactable GUI element is interacted with.
             * The callback function should have no parameters and no return value.
             *
             * @param callback The callback function to set.
             */
            void setCallback(std::function<void()> callback);

        protected:
            std::function<void()> _callback;

    };
}

#endif /* !INTERACTABLE_HPP_ */
