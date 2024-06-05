/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** RadioButtonList
*/

#ifndef RADIOBUTTONLIST_HPP_
#define RADIOBUTTONLIST_HPP_

#include "GUI/Input/RadioButton.hpp"
#include "GUI/Container.hpp"

/**
 * @brief The RadioButtonList class represents a list of radio buttons.
 *
 * This class inherits from the Container class and provides functionality to manage a list of RadioButton objects.
 * It allows the user to select a single radio button from the list.
 */
namespace EGE {
    class RadioButtonList : public Container<RadioButton>{
        public:
            /**
             * @brief Constructs a RadioButtonList object.
             */
            RadioButtonList();

            /**
             * @brief Destroys the RadioButtonList object.
             */
            ~RadioButtonList();

            /**
             * @brief Draws the RadioButtonList.
             *
             * This function overrides the draw() function of the base class.
             * It is responsible for drawing the RadioButtonList and its child radio buttons.
             */
            void draw() override;

        private:
            std::string _lastChecked; /**< The index of the last checked radio button in the list. */
    };
}

#endif /* !RADIOBUTTONLIST_HPP_ */
