/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** GUI
*/

#ifndef GUI_HPP_
#define GUI_HPP_

#include "Window.hpp"

#include <memory>

#include "imgui.h"

namespace EGE {

    /**
     * @brief The GUI class represents a graphical user interface.
     * 
     * This class provides an interface for creating and managing GUI elements.
     * It defines common methods for drawing, initializing, and managing the GUI.
     */
    class GUI {
        public:
            /**
             * @brief Destructor for the GUI class.
             * 
             * This is a virtual destructor to allow proper cleanup when inheriting from this class.
             */
            virtual ~GUI() = default;

            /**
             * @brief Draws the GUI.
             * 
             * This method is responsible for drawing the GUI elements on the screen.
             * It should be implemented by derived classes.
             */
            virtual void draw() = 0;

            /**
             * @brief Initializes the GUI with a window.
             * 
             * This method initializes the GUI with the specified window.
             * It should be called before using any other GUI methods.
             * 
             * @param window A pointer to the window to associate with the GUI.
             */
            void init(Window *window);

            /**
             * @brief Gets the name of the GUI.
             * 
             * This method returns the name of the GUI.
             * 
             * @return The name of the GUI.
             */
            std::string getName() const;

            /**
             * @brief Sets the name of the GUI.
             * 
             * This method sets the name of the GUI.
             * 
             * @param name The name to set for the GUI.
             */
            void setName(std::string name);

            /**
             * @brief Sets the window associated with the GUI.
             * 
             * This method sets the window associated with the GUI.
             * 
             * @param window A pointer to the window to associate with the GUI.
             */
            void setWindow(Window *window);

            /**
             * @brief Gets the window associated with the GUI.
             * 
             * This method returns the window associated with the GUI.
             * 
             * @return A pointer to the window associated with the GUI.
             */
            Window *getWindow() const;

            /**
             * @brief Sets the visibility of the GUI.
             * 
             * This method sets the visibility of the GUI.
             * 
             * @param visible The visibility state to set for the GUI.
             */
            void setVisible(bool visible);

            /**
             * @brief Checks if the GUI is visible.
             * 
             * This method checks if the GUI is currently visible.
             * 
             * @return True if the GUI is visible, false otherwise.
             */
            bool isVisible() const;

        protected:
            Window *_window; /**< A pointer to the window associated with the GUI. */
            std::string _name; /**< The name of the GUI. */
            bool _visible; /**< The visibility state of the GUI. */
    };
}

#endif /* !GUI_HPP_ */
