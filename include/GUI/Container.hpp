/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Container
*/

#ifndef CONTAINER_HPP_
#define CONTAINER_HPP_

#include "GUI/GUI.hpp"

namespace EGE {
    /**
     * @brief A container class that holds GUI elements.
     * 
     * This class is a template class that can hold any type of GUI element.
     * It provides methods to add and remove GUI elements from the container.
     */
    template<typename T>
    class Container : public GUI {
    public:
        /**
         * @brief Destructor for the Container class.
         */
        virtual ~Container() = default;

        /**
         * @brief Adds a GUI element to the container.
         * 
         * @param gui A pointer to the GUI element to be added.
         */
        void add(T *gui)
        {
            this->_elements.push_back(gui);
        }

        /**
         * @brief Removes a GUI element from the container.
         * 
         * @param gui A pointer to the GUI element to be removed.
         */
        void remove(T *gui)
        {
            this->_elements.erase(std::remove(this->_elements.begin(), this->_elements.end(), gui), this->_elements.end());
        }

    protected:
        std::vector<T *> _elements;
    };
}

#endif /* !CONTAINER_HPP_ */
