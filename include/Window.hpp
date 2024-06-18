/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** IWindow
*/

#pragma once

// Engine include
#include "Color.hpp"
#include "Error.hpp"
#include "Event.hpp"
#include "Maths/Vector2.hpp"
#include "OpenGL.hpp"

// C++ include
#include <concepts>
#include <exception>
#include <iostream>
#include <memory>
#include <string>

/**
 * @file Window.hpp
 * @brief Contains the declaration of the Window class.
*/

static int _glfwInitializations = 0;    /**< The number of GLFW initializations. */

/**
    * @namespace EGE
    * @brief Namespace for the ETIB Game Engine.
    *
    * The EGE namespace contains all the classes, functions, and variables
    * related to the ETIB Game Engine.
    */
namespace EGE {
    /**
     * @class Window
     * @brief Represents a window in the game engine.
     *
     * The Window class is responsible for creating and managing a window for the game engine.
     * It provides functions to control the window properties, such as title, size, position, and style.
     * The class also handles window events and provides functions to interact with the window, such as clearing the window, displaying the content, and polling events.
     */
    class Window {
        public:
            /**
             * @brief Represents an error that occurs in the Window class.
             */
            class WindowError : public Error {
                public:
                    /**
                     * @brief Constructs a WindowError object with the specified error message.
                     * @param message The error message.
                     */
                    WindowError(const std::string& message) : Error(message) {}
            };

            /**
             * @brief Enumerates the different styles that a window can have.
             */
            enum Styles {
                None = 0,           /**< No style. */
                Titlebar = 1 << 0,  /**< The window has a title bar. */
                Resize = 1 << 1,    /**< The window can be resized. */
                Close = 1 << 2,     /**< The window has a close button. */
                Fullscreen = 1 << 3,/**< The window is fullscreen. */
                Default = Titlebar | Resize | Close /**< The default window style. */
            };

            /**
             * @brief Constructs a new Window object.
             *
             * @param title The title of the window.
             * @param size The size of the window.
             * @param style The style of the window (optional, default is Styles::Default).
             */
            Window(const std::string& title, const EGE::Maths::Vector2<int>& size, const std::uint8_t& style = Styles::Default);

            /**
             * @brief Destructor for the Window class.
             *
             * This destructor is responsible for cleaning up any resources allocated by the Window class.
             * It is automatically called when an instance of the Window class goes out of scope or is explicitly deleted.
             */
            ~Window();

            /**
             * @brief Creates the window.
             *
             * This function is responsible for creating the window.
             * It initializes the necessary resources and sets up the window properties.
             *
             * @note This function should be called before any other window-related operations.
             */
            void create();

            /**
             * @brief Destroys the window.
             *
             * This function is responsible for destroying the window.
             * It releases any resources associated with the window.
             */
            void destroy();

            /**
             * @brief Clears the window with a specified color.
             *
             * This function clears the window with the specified color.
             * If no color is provided, it clears the window with black color by default.
             *
             * @param color The color to clear the window with (optional, default is black).
             */
            void clear(EGE::Color color = EGE::Color(0.0f, 0.0f, 0.0f, 1.0f));

            /**
             * @brief Displays the content of the window.
             *
             * This function displays the content of the window.
             * It updates the window's display buffer and shows the updated content on the screen.
             */
            void display();

            /**
             * @brief Polls events from the window.
             *
             * This function polls events from the window.
             * It checks for any user input or system events and processes them.
             */
            void pollEvents();

            /**
             * @brief Checks if the window is open.
             *
             * This function checks if the window is open.
             * It returns true if the window is open, false otherwise.
             *
             * @return True if the window is open, false otherwise.
             */
            bool isOpen();

            /**
             * @brief Closes the window.
             *
             * This function closes the window.
             * It releases any resources associated with the window and destroys the window.
             */
            void close();

            /**
             * Binds a trigger to the window.
             *
             * This function binds the specified trigger to the window. When the trigger is activated,
             * the window will respond accordingly.
             *
             * @param trigger The trigger to bind.
             * @return True if the trigger was successfully bound, false otherwise.
             */
            bool bindTrigger(const EGE::Event::Trigger& trigger);

            /**
             * @brief Binds a trigger to the window.
             *
             * This function binds the specified trigger to the window. When the trigger is activated,
             * the window will respond accordingly.
             *
             * @tparam _ArgTypes The argument types of the callback function.
             * @param trigger The trigger to bind.
             * @param callback The callback function to bind to the trigger.
             * @return True if the trigger was successfully bound, false otherwise.
             */
            template <typename... _ArgTypes, typename F>
            requires std::invocable<F, _ArgTypes...>
            bool bindWindowTrigger(EGE::Event::WindowTrigger trigger, F &&callback) {
                return this->_event->bindWindowTrigger<_ArgTypes...>(trigger, callback);
            }

            /**
             * @brief Unbinds a trigger from the window.
             *
             * This function removes the specified trigger from the window's event system.
             *
             * @param trigger The trigger to unbind.
             */
            void unbindTrigger(const EGE::Event::Trigger& trigger);

            /**
             * @brief Sets the title of the window.
             *
             * This function sets the title of the window.
             *
             * @param title The new title of the window.
             */
            void setTitle(const std::string& title);

            /**
             * @brief Sets the size of the window.
             *
             * This function sets the size of the window.
             *
             * @param width The new width of the window.
             * @param height The new height of the window.
             */
            void setSize(const int& width, const int& height);

            /**
             * @brief Sets the size of the window.
             *
             * This function sets the size of the window.
             *
             * @param size The new size of the window.
             */
            void setSize(const EGE::Maths::Vector2<int>& size);

            /**
             * @brief Sets the position of the window.
             *
             * This function sets the position of the window.
             *
             * @param x The new x-coordinate of the window.
             * @param y The new y-coordinate of the window.
             */
            void setPosition(const int& x, const int& y);

            /**
             * @brief Sets the position of the window.
             *
             * This function sets the position of the window.
             *
             * @param position The new position of the window.
             */
            void setPosition(const EGE::Maths::Vector2<int>& position);

            /**
             * @brief Sets the framerate limit of the window.
             *
             * This function sets the framerate limit of the window.
             * It limits the maximum number of frames per second that the window can render.
             *
             * @param limit The new framerate limit of the window.
             */
            void setFramerateLimit(const int& limit);

            /**
             * @brief Sets the visibility of the cursor in the window.
             *
             * This function sets the visibility of the cursor in the window.
             * If set to true, the cursor will be visible in the window.
             * If set to false, the cursor will be hidden in the window.
             *
             * @param visible True to make the cursor visible, false to hide the cursor.
             */
            void setCursorVisible(bool visible);

            /**
             * @brief Sets the activity state of the window.
             *
             * This function sets the activity state of the window.
             * If set to true, the window will be active and receive user input.
             * If set to false, the window will be inactive and not receive user input.
             *
             * @param active True to make the window active, false to make it inactive.
             */
            void setActive(bool active);

            /**
             * @brief Gets the position of the window.
             *
             * This function gets the position of the window.
             * It returns a vector containing the x and y coordinates of the window.
             *
             * @return The position of the window.
             */
            EGE::Maths::Vector2<int> getPosition();

            /**
             * @brief Gets the size of the window.
             *
             * This function gets the size of the window.
             * It returns a vector containing the width and height of the window.
             *
             * @return The size of the window.
             */
            EGE::Maths::Vector2<int> getSize();

            /**
             * @brief Gets the position of the mouse relative to the window.
             *
             * This function gets the position of the mouse relative to the window.
             * It returns a vector containing the x and y coordinates of the mouse.
             *
             * @return The position of the mouse relative to the window.
             */
            EGE::Maths::Vector2<int> getMousePosition();

            /**
             * @brief Gets the GLFW window object.
             *
             * @return The GLFWwindow pointer representing the window object.
             */
            GLFWwindow *getWindow() const;

        private:
            /**
             * @brief Initializes the GLFW library.
             *
             * This function initializes the GLFW library.
             * It sets up the necessary resources and prepares the library for window creation.
             */
            void _initializeGlfw();

            GLFWmonitor* _monitor;                  /**< The monitor to use for fullscreen mode. */
            const GLFWvidmode* _mode;               /**< The video mode of the monitor. */
            GLFWwindow* _window;                    /**< The GLFW window object. */
            std::string _title;                     /**< The title of the window. */
            EGE::Maths::Vector2<int> _size;         /**< The size of the window. */
            EGE::Maths::Vector2<int> _position;     /**< The position of the window. */
            int _framerateLimit;                    /**< The framerate limit of the window. */
            bool _cursorVisible;                    /**< The visibility of the cursor in the window. */
            bool _active;                           /**< The activity state of the window. */
            std::uint8_t _style;                    /**< The style of the window. */
            std::shared_ptr<EGE::Event> _event;     /**< The event handler for the window. */
    };
}