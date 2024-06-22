/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Container
*/

#ifndef CONTAINER_HPP_
#define CONTAINER_HPP_

#include "GUI/GUI.hpp"

#include <map>

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
         * @param name The name of the GUI element.
         */
        void add(T *gui, const std::string& name)
        {
            this->_elements[name] = gui;
        }

        /**
         * @brief Gets a GUI element from the container.
         *
         * @param name The name of the GUI element to get.
         * @return A pointer to the GUI element.
        */
        T *get(const std::string& name)
        {
            return this->_elements[name];
        }

        /**
         * @brief Removes a GUI element from the container.
         *
         * @param name The name of the GUI element to be removed.
         */
        void remove(const std::string& name)
        {
            this->_elements.erase(name);
        }

        /**
         * @brief Gets all the GUI elements in the container.
         *
         * @return A map of GUI elements, where the key is the name of the element and the value is a pointer to the element.
         */
        std::map<std::string, T *> getElements() const
        {
            return this->_elements;
        }

        /**
         * @brief Clears all the GUI elements in the container.
         */
        void clear()
        {
            this->_elements.clear();
        }

    protected:
        std::map<std::string, T *> _elements; /**< The map of GUI elements in the container. */
    };
}

#endif /* !CONTAINER_HPP_ */
