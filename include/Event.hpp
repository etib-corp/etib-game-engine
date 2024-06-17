/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Event
*/

#pragma once

// Engine include
#include "Error.hpp"
#include "OpenGL.hpp"

// C++ include
#include <algorithm>
#include <concepts>
#include <cstdarg>
#include <cstdint>
#include <functional>
#include <iostream>
#include <vector>

/**
 * @file Event.hpp
 * @brief Contains the declaration of the Eventindow class.
*/

/**
    * @namespace EGE
    * @brief Namespace for the ETIB Game Engine.
    *
    * The EGE namespace contains all the classes, functions, and variables
    * related to the ETIB Game Engine.
    */
namespace EGE {

    /**
     * @class Event
     * @brief Represents an event in the game engine.
     *
     * The Event class provides functionality to handle various types of events, such as keyboard, mouse, window, joystick, and trigger events.
     * It allows registering triggers and callbacks to be executed when specific events occur.
     */
    class Event {
        public:
            /**
             * @class EventError
             * @brief Represents an error that occurred during an event.
             *
             * This class is derived from the base class Error and provides a specific error type for events.
             */
            class EventError : public Error {
                public:
                    /**
                     * @brief Constructs an EventError object with the given error message.
                     *
                     * @param message The error message associated with the event error.
                     */
                    EventError(std::string const &message) : Error(message) {}
            };

            /**
             * @enum Type
             * @brief The enumeration of event types.
             *
             * This enumeration defines the different types of events that can occur in the game engine.
             * The event types include KEYBOARD, MOUSE, JOYSTICK, and WINDOW.
             */
            enum Type {
                Keyboard,                                           /**< Event type for keyboard events. */
                Mouse,                                              /**< Event type for mouse events. */
                JoystickButton,                                     /**< Event type for joystick events. */
                JoystickAxis,                                       /**< Event type for joystick events. */
                Window                                              /**< Event type for window events. */
                // TODO: Special check for binding window events because they are handled by GLFW with a callback
            };

            /**
             * @enum Mode
             * @brief Enumeration representing different modes of an event.
             *
             * This enumeration defines the different modes of an event, such as MOVED, PRESSED, JUST_PRESSED, RELEASED, and JUST_RELEASED.
             */
            enum Mode {
                Moved = 0,                                          /**< Event mode for movement. */
                Changed = 0,                                        /**< Event mode for window state change. */
                Pressed = 1,                                        /**< Event mode for button press. */
                JustPressed = 2,                                    /**< Event mode for just pressed button. */
                Released = 4,                                       /**< Event mode for button release. */
                JustReleased = 8,                                   /**< Event mode for just released button. */
            };

            /**
             * @enum Key
             * @brief Enumeration of key codes.
             */
            enum Key {
                KeyA = GLFW_KEY_A,                                  /**< Key code for the A key. */
                KeyB = GLFW_KEY_B,                                  /**< Key code for the B key. */
                KeyC = GLFW_KEY_C,                                  /**< Key code for the C key. */
                KeyD = GLFW_KEY_D,                                  /**< Key code for the D key. */
                KeyE = GLFW_KEY_E,                                  /**< Key code for the E key. */
                KeyF = GLFW_KEY_F,                                  /**< Key code for the F key. */
                KeyG = GLFW_KEY_G,                                  /**< Key code for the G key. */
                KeyH = GLFW_KEY_H,                                  /**< Key code for the H key. */
                KeyI = GLFW_KEY_I,                                  /**< Key code for the I key. */
                KeyJ = GLFW_KEY_J,                                  /**< Key code for the J key. */
                KeyK = GLFW_KEY_K,                                  /**< Key code for the K key. */
                KeyL = GLFW_KEY_L,                                  /**< Key code for the L key. */
                KeyM = GLFW_KEY_M,                                  /**< Key code for the M key. */
                KeyN = GLFW_KEY_N,                                  /**< Key code for the N key. */
                KeyO = GLFW_KEY_O,                                  /**< Key code for the O key. */
                KeyP = GLFW_KEY_P,                                  /**< Key code for the P key. */
                KeyQ = GLFW_KEY_Q,                                  /**< Key code for the Q key. */
                KeyR = GLFW_KEY_R,                                  /**< Key code for the R key. */
                KeyS = GLFW_KEY_S,                                  /**< Key code for the S key. */
                KeyT = GLFW_KEY_T,                                  /**< Key code for the T key. */
                KeyU = GLFW_KEY_U,                                  /**< Key code for the U key. */
                KeyV = GLFW_KEY_V,                                  /**< Key code for the V key. */
                KeyW = GLFW_KEY_W,                                  /**< Key code for the W key. */
                KeyX = GLFW_KEY_X,                                  /**< Key code for the X key. */
                KeyY = GLFW_KEY_Y,                                  /**< Key code for the Y key. */
                KeyZ = GLFW_KEY_Z,                                  /**< Key code for the Z key. */
                KeyBacktick = GLFW_KEY_GRAVE_ACCENT,                /**< Key code for the backtick key. */
                Key0 = GLFW_KEY_0,                                  /**< Key code for the 0 key. */
                Key1 = GLFW_KEY_1,                                  /**< Key code for the 1 key. */
                Key2 = GLFW_KEY_2,                                  /**< Key code for the 2 key. */
                Key3 = GLFW_KEY_3,                                  /**< Key code for the 3 key. */
                Key4 = GLFW_KEY_4,                                  /**< Key code for the 4 key. */
                Key5 = GLFW_KEY_5,                                  /**< Key code for the 5 key. */
                Key6 = GLFW_KEY_6,                                  /**< Key code for the 6 key. */
                Key7 = GLFW_KEY_7,                                  /**< Key code for the 7 key. */
                Key8 = GLFW_KEY_8,                                  /**< Key code for the 8 key. */
                Key9 = GLFW_KEY_9,                                  /**< Key code for the 9 key. */
                KeyMinus = GLFW_KEY_MINUS,                          /**< Key code for the minus key. */
                KeyEqual = GLFW_KEY_EQUAL,                          /**< Key code for the equal key. */
                KeyLeftBracket = GLFW_KEY_LEFT_BRACKET,             /**< Key code for the left bracket key. */
                KeyRightBracket = GLFW_KEY_RIGHT_BRACKET,           /**< Key code for the right bracket key. */
                KeyBackslash = GLFW_KEY_BACKSLASH,                  /**< Key code for the backslash key. */
                KeySemicolon = GLFW_KEY_SEMICOLON,                  /**< Key code for the semicolon key. */
                KeyApostrophe = GLFW_KEY_APOSTROPHE,                /**< Key code for the apostrophe key. */
                KeyComma = GLFW_KEY_COMMA,                          /**< Key code for the comma key. */
                KeyPeriod = GLFW_KEY_PERIOD,                        /**< Key code for the period key. */
                KeySlash = GLFW_KEY_SLASH,                          /**< Key code for the slash key. */
                KeyCapsLock = GLFW_KEY_CAPS_LOCK,                   /**< Key code for the caps lock key. */
                KeyWorld1 = GLFW_KEY_WORLD_1,                       /**< Key code for the world 1 key. */
                KeyWorld2 = GLFW_KEY_WORLD_2,                       /**< Key code for the world 2 key. */
                KeySuper = GLFW_KEY_LEFT_SUPER,                     /**< Key code for the left super key. */
                KeyNumLock = GLFW_KEY_NUM_LOCK,                     /**< Key code for the num lock key. */
                KeyPadDivide = GLFW_KEY_KP_DIVIDE,                  /**< Key code for the keypad divide key. */
                KeyPadMultiply = GLFW_KEY_KP_MULTIPLY,              /**< Key code for the keypad multiply key. */
                KeyPadSubtract = GLFW_KEY_KP_SUBTRACT,              /**< Key code for the keypad subtract key. */
                KeyPadAdd = GLFW_KEY_KP_ADD,                        /**< Key code for the keypad add key. */
                KeyPadDecimal = GLFW_KEY_KP_DECIMAL,                /**< Key code for the keypad decimal key. */
                KeyPadEnter = GLFW_KEY_KP_ENTER,                    /**< Key code for the keypad enter key. */
                KeyPad0 = GLFW_KEY_KP_0,                            /**< Key code for the keypad 0 key. */
                KeyPad1 = GLFW_KEY_KP_1,                            /**< Key code for the keypad 1 key. */
                KeyPad2 = GLFW_KEY_KP_2,                            /**< Key code for the keypad 2 key. */
                KeyPad3 = GLFW_KEY_KP_3,                            /**< Key code for the keypad 3 key. */
                KeyPad4 = GLFW_KEY_KP_4,                            /**< Key code for the keypad 4 key. */
                KeyPad5 = GLFW_KEY_KP_5,                            /**< Key code for the keypad 5 key. */
                KeyPad6 = GLFW_KEY_KP_6,                            /**< Key code for the keypad 6 key. */
                KeyPad7 = GLFW_KEY_KP_7,                            /**< Key code for the keypad 7 key. */
                KeyPad8 = GLFW_KEY_KP_8,                            /**< Key code for the keypad 8 key. */
                KeyPad9 = GLFW_KEY_KP_9,                            /**< Key code for the keypad 9 key. */
                KeySpace = GLFW_KEY_SPACE,                          /**< Key code for the space key. */
                KeyLShift = GLFW_KEY_LEFT_SHIFT,                    /**< Key code for the left shift key. */
                KeyRShift = GLFW_KEY_RIGHT_SHIFT,                   /**< Key code for the right shift key. */
                KeyLCtrl = GLFW_KEY_LEFT_CONTROL,                   /**< Key code for the left control key. */
                KeyRCtrl = GLFW_KEY_RIGHT_CONTROL,                  /**< Key code for the right control key. */
                KeyLAlt = GLFW_KEY_LEFT_ALT,                        /**< Key code for the left alt key. */
                KeyRAlt = GLFW_KEY_RIGHT_ALT,                       /**< Key code for the right alt key. */
                KeyTab = GLFW_KEY_TAB,                              /**< Key code for the tab key. */
                KeyEnter = GLFW_KEY_ENTER,                          /**< Key code for the enter key. */
                KeyBackspace = GLFW_KEY_BACKSPACE,                  /**< Key code for the backspace key. */
                KeyEscape = GLFW_KEY_ESCAPE,                        /**< Key code for the escape key. */
                KeyDelete = GLFW_KEY_DELETE,                        /**< Key code for the delete key. */
                KeyInsert = GLFW_KEY_INSERT,                        /**< Key code for the insert key. */
                KeyHome = GLFW_KEY_HOME,                            /**< Key code for the home key. */
                KeyPause = GLFW_KEY_PAUSE,                          /**< Key code for the pause key. */
                KeyPrntScrn = GLFW_KEY_PRINT_SCREEN,                /**< Key code for the print screen key. */
                KeyUp = GLFW_KEY_UP,                                /**< Key code for the up key. */
                KeyDown = GLFW_KEY_DOWN,                            /**< Key code for the down key. */
                KeyLeft = GLFW_KEY_LEFT,                            /**< Key code for the left key. */
                KeyRight = GLFW_KEY_RIGHT,                          /**< Key code for the right key. */
                KeyF1 = GLFW_KEY_F1,                                /**< Key code for the F1 key. */
                KeyF2 = GLFW_KEY_F2,                                /**< Key code for the F2 key. */
                KeyF3 = GLFW_KEY_F3,                                /**< Key code for the F3 key. */
                KeyF4 = GLFW_KEY_F4,                                /**< Key code for the F4 key. */
                KeyF5 = GLFW_KEY_F5,                                /**< Key code for the F5 key. */
                KeyF6 = GLFW_KEY_F6,                                /**< Key code for the F6 key. */
                KeyF7 = GLFW_KEY_F7,                                /**< Key code for the F7 key. */
                KeyF8 = GLFW_KEY_F8,                                /**< Key code for the F8 key. */
                KeyF9 = GLFW_KEY_F9,                                /**< Key code for the F9 key. */
                KeyF10 = GLFW_KEY_F10,                              /**< Key code for the F10 key. */
                KeyF11 = GLFW_KEY_F11,                              /**< Key code for the F11 key. */
                KeyF12 = GLFW_KEY_F12,                              /**< Key code for the F12 key. */
                KeySpecial1 = GLFW_KEY_F13,                         /**< Key code for the special 1 key. */
                KeySpecial2 = GLFW_KEY_F14,                         /**< Key code for the special 2 key. */
                KeySpecial3 = GLFW_KEY_F15,                         /**< Key code for the special 3 key. */
                KeySpecial4 = GLFW_KEY_F16,                         /**< Key code for the special 4 key. */
                KeySpecial5 = GLFW_KEY_F17,                         /**< Key code for the special 5 key. */
                KeySpecial6 = GLFW_KEY_F18,                         /**< Key code for the special 6 key. */
                KeySpecial7 = GLFW_KEY_F19,                         /**< Key code for the special 7 key. */
                KeySpecial8 = GLFW_KEY_F20,                         /**< Key code for the special 8 key. */
                KeySpecial9 = GLFW_KEY_F21,                         /**< Key code for the special 9 key. */
                KeySpecial10 = GLFW_KEY_F22,                        /**< Key code for the special 10 key. */
                KeySpecial11 = GLFW_KEY_F23,                        /**< Key code for the special 11 key. */
                KeySpecial12 = GLFW_KEY_F24,                        /**< Key code for the special 12 key. */
                KeySpecial13 = GLFW_KEY_F25,                        /**< Key code for the special 13 key. */
                KeyPageUp = GLFW_KEY_PAGE_UP,                       /**< Key code for the page up key. */
                KeyPageDown = GLFW_KEY_PAGE_DOWN,                   /**< Key code for the page down key. */
                KeyScrollLock = GLFW_KEY_SCROLL_LOCK,               /**< Key code for the scroll lock key. */
                KeyEnd = GLFW_KEY_END,                              /**< Key code for the end key. */
                KeyMenu = GLFW_KEY_MENU,                            /**< Key code for the menu key. */
            };

            /**
             * @enum Mouse
             * @brief Enumeration of mouse buttons.
             */
            enum Mouse {
                MouseLeft = GLFW_MOUSE_BUTTON_LEFT,                 /**< Mouse button code for the left mouse button. */
                MouseRight = GLFW_MOUSE_BUTTON_RIGHT,               /**< Mouse button code for the right mouse button. */
                MouseMiddle = GLFW_MOUSE_BUTTON_MIDDLE,             /**< Mouse button code for the middle mouse button. */
                Mouse1 = GLFW_MOUSE_BUTTON_1,                       /**< Mouse button code for the first mouse button. */
                Mouse2 = GLFW_MOUSE_BUTTON_2,                       /**< Mouse button code for the second mouse button. */
                Mouse3 = GLFW_MOUSE_BUTTON_3,                       /**< Mouse button code for the third mouse button. */
                Mouse4 = GLFW_MOUSE_BUTTON_4,                       /**< Mouse button code for the fourth mouse button. */
                Mouse5 = GLFW_MOUSE_BUTTON_5,                       /**< Mouse button code for the fifth mouse button. */
                Mouse6 = GLFW_MOUSE_BUTTON_6,                       /**< Mouse button code for the sixth mouse button. */
                Mouse7 = GLFW_MOUSE_BUTTON_7,                       /**< Mouse button code for the seventh mouse button. */
                Mouse8 = GLFW_MOUSE_BUTTON_8,                       /**< Mouse button code for the eighth mouse button. */
                Cursor,                                          /**< Mouse button code for mouse movement. */
            };

            /**
             * @enum Joystick
             * @brief Enum representing joystick buttons.
             */
            enum JoystickButton {
                JoystickA = GLFW_GAMEPAD_BUTTON_A,                  /**< Joystick button code for the A button. */
                JoystickCross = JoystickA,                          /**< Joystick button code for the cross button. */
                JoystickB = GLFW_GAMEPAD_BUTTON_B,                  /**< Joystick button code for the B button. */
                JoystickCircle = JoystickB,                         /**< Joystick button code for the circle button. */
                JoystickX = GLFW_GAMEPAD_BUTTON_X,                  /**< Joystick button code for the X button. */
                JoystickSquare = JoystickX,                         /**< Joystick button code for the square button. */
                JoystickY = GLFW_GAMEPAD_BUTTON_Y,                  /**< Joystick button code for the Y button. */
                JoystickTriangle = JoystickY,                       /**< Joystick button code for the triangle button. */
                JoystickLB = GLFW_GAMEPAD_BUTTON_LEFT_BUMPER,       /**< Joystick button code for the left bumper button. */
                JoystickRB = GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER,      /**< Joystick button code for the right bumper button. */
                JoystickBack = GLFW_GAMEPAD_BUTTON_BACK,            /**< Joystick button code for the back button. */
                JoystickStart = GLFW_GAMEPAD_BUTTON_START,          /**< Joystick button code for the start button. */
                JoystickGuide = GLFW_GAMEPAD_BUTTON_GUIDE,          /**< Joystick button code for the guide button. */
                JoystickLThumb = GLFW_GAMEPAD_BUTTON_LEFT_THUMB,    /**< Joystick button code for the left thumb button. */
                JoystickRThumb = GLFW_GAMEPAD_BUTTON_RIGHT_THUMB,   /**< Joystick button code for the right thumb button. */
                JoystickUp = GLFW_GAMEPAD_BUTTON_DPAD_UP,           /**< Joystick button code for the up button. */
                JoystickRight = GLFW_GAMEPAD_BUTTON_DPAD_RIGHT,     /**< Joystick button code for the right button. */
                JoystickDown = GLFW_GAMEPAD_BUTTON_DPAD_DOWN,       /**< Joystick button code for the down button. */
                JoystickLeft = GLFW_GAMEPAD_BUTTON_DPAD_LEFT,       /**< Joystick button code for the left button. */
            };

            enum JoystickAxis {
                JoystickLX = GLFW_GAMEPAD_AXIS_LEFT_X,              /**< Joystick axis code for the left X axis. */
                JoystickLY = GLFW_GAMEPAD_AXIS_LEFT_Y,              /**< Joystick axis code for the left Y axis. */
                JoystickLT = GLFW_GAMEPAD_AXIS_RIGHT_X,             /**< Joystick axis code for the left trigger axis. */
                JoystickRX = GLFW_GAMEPAD_AXIS_RIGHT_Y,             /**< Joystick axis code for the right X axis. */
                JoystickRY = GLFW_GAMEPAD_AXIS_LEFT_TRIGGER,        /**< Joystick axis code for the right Y axis.*/
                JoystickRT = GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER,       /**< Joystick axis code for the right trigger axis. */
            };

            /**
             * @enum Window
             * @brief Enumerations for window events.
             */
            enum WindowTrigger {
                WindowClose,                                        /**< Window event for closing the window. */
                WindowFocus,                                        /**< Window event for focusing the window. */
                WindowLostFocus,                                    /**< Window event for losing focus. */
                WindowFileDrop,                                     /**< Window event for dropping a file. */
                WindowScroll,                                       /**< Window event for scrolling the window. */
                WindowContentScaleChanged,                          /**< Window event for changing the content scale. */
                WindowFramebufferResized,                           /**< Window event for resizing the framebuffer. */
                WindowIconified,                                    /**< Window event for iconifying the window. */
                WindowMaximized,                                    /**< Window event for maximizing the window. */
                WindowMoved,                                        /**< Window event for moving the window. */
                WindowResized,                                      /**< Window event for resizing the window. */
                WindowRefreshed,                                    /**< Window event for refreshing the window. */
                WindowCursorMoved,                                  /**< Window event for moving the cursor. */
            };

            #include "GlfwCallback.hpp"

            /**
             * @class Trigger
             * @brief The Trigger class represents a trigger event.
             *
             * The Trigger class represents a trigger event that can be registered within the Event class.
             */
            class Trigger {
            public:
                /**
                 * @brief Constructs a Trigger object.
                 *
                 * @param type The type of the trigger.
                 * @param trigger The trigger value.
                 * @param mode The mode of the trigger.
                 * @param callback The callback function to be called when the trigger is activated.
                 * @param joystickId The ID of the joystick associated with the trigger (optional, default is -1).
                 */
                Trigger(Type type, std::uint32_t trigger, Mode mode, std::function<void()> callback, std::uint8_t joystickId = -1);

                /**
                 * @brief Constructs a Trigger object.
                 *
                 * @param type The type of the trigger.
                 * @param trigger The trigger value.
                 * @param mode The mode of the trigger.
                 * @param callback The callback function to be called when the trigger is activated.
                 * @param joystickId The ID of the joystick associated with the trigger (optional, default is -1).
                 * @note This constructor is used for joystick axis events.
                */
                Trigger(Type type, std::uint32_t trigger, Mode mode, std::function<void(float)> callback, std::uint8_t joystickId = -1);

                /**
                 * @brief Destroys the Trigger object.
                 */
                ~Trigger();

                /**
                 * @brief Gets the trigger value.
                 *
                 * @return The trigger value.
                 */
                std::uint32_t getTrigger() const;

                /**
                 * @brief Gets the type of the trigger.
                 *
                 * @return The type of the trigger.
                 */
                Type getType() const;

                /**
                 * @brief Gets the ID of the joystick associated with the trigger.
                 *
                 * @return The ID of the joystick associated with the trigger.
                 */
                std::int8_t getJoystickId() const;

                /**
                 * @brief Gets the mode of the trigger.
                 *
                 * @return The mode of the trigger.
                 */
                Mode getMode() const;

                /**
                 * @brief Retrieves the callback function associated with this event.
                 *
                 * @return The callback function associated with this event.
                 */
                std::function<void()> getCallback() const;

                                /**
                 * @brief Retrieves the callback function associated with this event.
                 *
                 * @return The callback function associated with this event.
                 * @note This function is used for joystick axis events.
                 */
                std::function<void(float)> getJoystickAxisCallback() const;

                /**
                 * @brief Checks if the trigger is currently pressed.
                 *
                 * @return True if the trigger is pressed, false otherwise.
                 */
                bool isPressed() const;

                /**
                 * @brief Sets the pressed state of the trigger.
                 *
                 * @param pressed The pressed state to set.
                 */
                void setPressed(bool pressed);

                /**
                 * @brief Sets the callback function to be called when the trigger is activated.
                 *
                 * @param callback The callback function to be set.
                 */
                void setCallback(std::function<void()> callback);

                /**
                 * @brief Checks if the current Trigger object is equal to another Trigger object.
                 *
                 * @param other The Trigger object to compare with.
                 * @return true if the Trigger objects are equal, false otherwise.
                 */
                bool operator==(const Trigger &other) const;

                /**
                 * @brief Assignment operator.
                 *
                 * This assignment operator assigns the values of the `other` object to the current object.
                 *
                 * @param other The `Trigger` object to be assigned.
                 * @return A reference to the current `Trigger` object after assignment.
                 */
                EGE::Event::Trigger& operator=(const Trigger &other);

            private:
                const std::uint32_t _trigger;                       /**< The trigger value. */
                const Type _type;                                   /**< The type of the trigger. */
                std::function<void()> _callback;                    /**< The callback function to be called when the trigger is activated. */
                std::function<void(float)> _joystickAxisCallback;   /**< The callback function to be called when the joystickAxis is moved. */
                const std::int8_t _joystickId;                      /**< The ID of the joystick associated with the trigger. */
                Mode _mode;                                         /**< The mode of the trigger. */
                bool _pressed;                                      /**< The pressed state of the trigger. */
            };

            /**
             * @brief Constructs an Event object.
             *
             * @param window The GLFWwindow associated with the event.
             */
            Event(GLFWwindow *window);

            /**
             * @brief Destructor for the Event class.
             */
            ~Event();

            /**
             * @brief Binds a trigger to the event.
             *
             * @param trigger The trigger to bind.
             * @return True if the trigger was successfully bound, false otherwise.
             */
            bool bindTrigger(const Trigger& trigger);

            /**
             * @brief Binds a callback function to a specific window trigger event.
             *
             * @tparam _ArgTypes The argument types of the callback function.
             * @tparam F The type of the callback function.
             * @param trigger The window trigger event to bind the callback to.
             * @param callback The callback function to bind.
             * @return True if the binding was successful, false otherwise.
             */
            template <typename... _ArgTypes, typename F>
            requires std::invocable<F, _ArgTypes...>
            bool bindWindowTrigger(const EGE::Event::WindowTrigger &trigger, F &&callback)
            {
                switch (trigger)
                {
                case EGE::Event::WindowTrigger::WindowClose:
                    GlfwWindowCloseCallbackFunction::getInstance(callback, true);
                    glfwSetWindowCloseCallback(this->_window, [](GLFWwindow *window) {
                        glfwSetWindowShouldClose(window, GL_FALSE);
                        GlfwWindowCloseCallbackFunction::getInstance()->call(window);
                    });
                    return true;
                case EGE::Event::WindowTrigger::WindowFocus:
                    GlfwWindowFocusCallbackFunction::getInstance(callback, true);
                    glfwSetWindowFocusCallback(this->_window, [](GLFWwindow *window, int focused) {
                        if (focused)
                            GlfwWindowFocusCallbackFunction::getInstance()->call(window, focused);
                        if (!focused)
                            GlfwWindowLostFocusCallbackFunction::getInstance()->call(window, focused);
                    });
                    return true;
                case EGE::Event::WindowTrigger::WindowLostFocus:
                    GlfwWindowLostFocusCallbackFunction::getInstance(callback, true);
                    glfwSetWindowFocusCallback(this->_window, [](GLFWwindow *window, int focused) {
                        if (focused)
                            GlfwWindowFocusCallbackFunction::getInstance()->call(window, focused);
                        if (!focused)
                            GlfwWindowLostFocusCallbackFunction::getInstance()->call(window, focused);
                    });
                    return true;
                case EGE::Event::WindowTrigger::WindowFileDrop:
                    GlfwWindowFileDropCallbackFunction::getInstance(callback, true);
                    glfwSetDropCallback(this->_window, [](GLFWwindow *window, int nb, const char* paths[]) {
                        GlfwWindowFileDropCallbackFunction::getInstance()->call(window, nb, paths);
                    });
                    return true;
                case EGE::Event::WindowTrigger::WindowScroll:
                    GlfwWindowScrollCallbackFunction::getInstance(callback, true);
                    glfwSetScrollCallback(this->_window, [](GLFWwindow *window, double xoffset, double yoffset) {
                        GlfwWindowScrollCallbackFunction::getInstance()->call(window, xoffset, yoffset);
                    });
                    return true;
                case EGE::Event::WindowTrigger::WindowContentScaleChanged:
                    GlfwWindowContentScaleChangedCallbackFunction::getInstance(callback, true);
                    glfwSetWindowContentScaleCallback(this->_window, [](GLFWwindow *window, float x, float y) {
                        GlfwWindowContentScaleChangedCallbackFunction::getInstance()->call(window, x, y);
                    });
                    return true;
                case EGE::Event::WindowTrigger::WindowFramebufferResized:
                    GlfwWindowFramebufferResizedCallbackFunction::getInstance(callback, true);
                    glfwSetFramebufferSizeCallback(this->_window, [](GLFWwindow *window, int width, int height) {
                        GlfwWindowFramebufferResizedCallbackFunction::getInstance()->call(window, width, height);
                    });
                    return true;
                case EGE::Event::WindowTrigger::WindowIconified:
                    GlfwWindowIconifiedCallbackFunction::getInstance(callback, true);
                    glfwSetWindowIconifyCallback(this->_window, [](GLFWwindow *window, int iconified) {
                        GlfwWindowIconifiedCallbackFunction::getInstance()->call(window, iconified);
                    });
                    return true;
                case EGE::Event::WindowTrigger::WindowMaximized:
                    GlfwWindowMaximizedCallbackFunction::getInstance(callback, true);
                    glfwSetWindowMaximizeCallback(this->_window, [](GLFWwindow *window, int maximized) {
                        GlfwWindowMaximizedCallbackFunction::getInstance()->call(window, maximized);
                    });
                    return true;
                case EGE::Event::WindowTrigger::WindowMoved:
                    GlfwWindowMovedCallbackFunction::getInstance(callback, true);
                    glfwSetWindowPosCallback(this->_window, [](GLFWwindow *window, int x, int y) {
                        GlfwWindowMovedCallbackFunction::getInstance()->call(window, x, y);
                    });
                    return true;
                case EGE::Event::WindowTrigger::WindowResized:
                    GlfwWindowResizedCallbackFunction::getInstance(callback, true);
                    glfwSetWindowSizeCallback(this->_window, [](GLFWwindow *window, int width, int height) {
                        GlfwWindowResizedCallbackFunction::getInstance()->call(window, width, height);
                    });
                    return true;
                case EGE::Event::WindowTrigger::WindowRefreshed:
                    GlfwWindowRefreshedCallbackFunction::getInstance(callback, true);
                    glfwSetWindowRefreshCallback(this->_window, [](GLFWwindow *window) {
                        GlfwWindowRefreshedCallbackFunction::getInstance()->call(window);
                    });
                    return true;
                case EGE::Event::WindowTrigger::WindowCursorMoved:
                    GlfwCursorCallbackFunction::getInstance(callback, true);
                    glfwSetCursorPosCallback(this->_window, [](GLFWwindow *window, double xpos, double ypos) {
                        // std::cout << "Cursor moved to (" << xpos << ", " << ypos << ")" << std::endl;
                        GlfwCursorCallbackFunction::getInstance()->call(window, xpos, ypos);
                    });
                default:
                    return false;
                }
            }

            /**
             * @brief Unbinds a trigger from the event.
             *
             * This function removes the specified trigger from the event's list of triggers.
             *
             * @param trigger The trigger to unbind.
             */
            void unbindTrigger(const Trigger& trigger);

            /**
             * @brief Polls events from the event queue.
             *
             * This function retrieves and processes events from the event queue.
             * It should be called in the main game loop to handle user input and other events.
             */
            void pollEvents();

        private:
            std::vector<Trigger> _triggers;                         /**< A container that holds a collection of Trigger objects. */
            GLFWwindow *_window;                                    /**< The window associated with the event. */
            bool _joystickEnabled;                                  /**< A flag indicating whether joystick events are enabled. */
    };
}
