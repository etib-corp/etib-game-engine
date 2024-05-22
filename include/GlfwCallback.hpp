/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** GlfwCallback
*/

#pragma once

// Engine include
#include "OpenGL.hpp"

// C++ include
#include <algorithm>
#include <cstdarg>
#include <cstdint>
#include <functional>
#include <iostream>

/**
 * @class GlfwWindowCloseCallbackFunction
 * @brief A class that represents a callback function for the GLFW window close event.
 *
 * This class provides a way to register a callback function that will be called when the GLFW window is closed.
 * Only one instance of this class can exist at a time, and it can be accessed using the getInstance() method.
 * The callback function must be invocable with a GLFWwindow* parameter.
 */
class GlfwWindowCloseCallbackFunction {
    public:

        /**
         * @brief Deleted copy constructor.
         */
        GlfwWindowCloseCallbackFunction(const GlfwWindowCloseCallbackFunction &) = delete;

        /**
         * @brief Deleted copy assignment operator.
         */
        GlfwWindowCloseCallbackFunction &operator=(const GlfwWindowCloseCallbackFunction &) = delete;

        /**
         * @brief Get the instance of the GlfwWindowCloseCallbackFunction class.
         *
         * If an instance already exists and the 'force' parameter is set to true, the existing instance will be deleted and a new one will be created.
         * If an instance does not exist, a new one will be created.
         *
         * @tparam F The type of the callback function.
         * @param callback The callback function to be registered.
         * @param force Whether to force the creation of a new instance.
         * @return A pointer to the instance of the GlfwWindowCloseCallbackFunction class.
         */
        template<typename F>
        static GlfwWindowCloseCallbackFunction *getInstance(F &&callback, bool force = false)
        {
            if constexpr(std::invocable<F, GLFWwindow *>) {
                if (force && _instance) {
                    delete _instance;
                    _instance = nullptr;
                }
                if (!_instance)
                    _instance = new GlfwWindowCloseCallbackFunction(callback);
            }
            return _instance;
        }

        /**
         * @brief Get the instance of the GlfwWindowCloseCallbackFunction class.
         *
         * @return A pointer to the instance of the GlfwWindowCloseCallbackFunction class.
         */
        static GlfwWindowCloseCallbackFunction *getInstance()
        {
            return _instance;
        }

        /**
         * @brief Call the callback function with the specified arguments.
         *
         * If a callback function is registered, it will be called with the specified arguments.
         *
         * @tparam _ArgTypes The types of the arguments.
         * @param args The arguments to be passed to the callback function.
         */
        template<typename... _ArgTypes>
        void call(_ArgTypes... args)
        {
            if (this->_callback)
                this->_callback(args...);
        }
    private:
        /**
         * @brief Private constructor.
         *
         * @tparam F The type of the callback function.
         * @param callback The callback function to be registered.
         */
        template<typename F>
        requires std::invocable<F, GLFWwindow *>
        GlfwWindowCloseCallbackFunction(F &&callback) : _callback(callback) {}

        /**
         * @brief Destructor.
         */
        ~GlfwWindowCloseCallbackFunction() {}

        static GlfwWindowCloseCallbackFunction *_instance;                      /**< The instance of the GlfwWindowCloseCallbackFunction class. */
        std::function<void(GLFWwindow *)> _callback;                            /**< The callback function to be called when the GLFW window is closed. */
};

/**
 * @class GlfwWindowFocusCallbackFunction
 * @brief Represents a singleton callback function for GLFW window focus events.
 *
 * This class provides a singleton implementation for a callback function that is invoked when a GLFW window gains or loses focus.
 * It allows registering a callback function that takes a GLFWwindow pointer and an integer as arguments.
 * The callback function can be set using the `getInstance` method.
 * The `call` method is used to invoke the registered callback function.
 */
class GlfwWindowFocusCallbackFunction {
    public:
        /**
         * @brief Deleted copy constructor.
         */
        GlfwWindowFocusCallbackFunction(const GlfwWindowFocusCallbackFunction &) = delete;

        /**
         * @brief Deleted copy assignment operator.
         */
        GlfwWindowFocusCallbackFunction &operator=(const GlfwWindowFocusCallbackFunction &) = delete;

        /**
         * Returns an instance of the GlfwWindowFocusCallbackFunction with the specified callback function.
         *
         * @tparam F The type of the callback function.
         * @param callback The callback function to be invoked when the window focus changes.
         * @param force If set to true, forces the creation of a new instance even if one already exists.
         * @return A pointer to the instance of the GlfwWindowFocusCallbackFunction.
         */
        template<typename F>
        static GlfwWindowFocusCallbackFunction *getInstance(F &&callback, bool force = false)
        {
            if constexpr(std::invocable<F, GLFWwindow *, int>) {
                if (force && _instance) {
                    delete _instance;
                    _instance = nullptr;
                }
                if (!_instance)
                    _instance = new GlfwWindowFocusCallbackFunction(callback);
            }
            return _instance;
        }

        /**
         * Returns the instance of the GlfwWindowFocusCallbackFunction.
         *
         * @return A pointer to the instance of the GlfwWindowFocusCallbackFunction.
         */
        static GlfwWindowFocusCallbackFunction *getInstance()
        {
            return _instance;
        }

        /**
         * @brief Calls the callback function with the provided arguments.
         *
         * This function checks if a callback function is set and then calls it with the provided arguments.
         *
         * @tparam _ArgTypes The types of the arguments.
         * @param args The arguments to be passed to the callback function.
         */
        template<typename... _ArgTypes>
        void call(_ArgTypes... args)
        {
            if (this->_callback)
                this->_callback(args...);
        }
    private:
        /**
         * @brief Constructor for the GlfwWindowFocusCallbackFunction class.
         *
         * This constructor takes a callable object as a parameter and initializes the _callback member variable.
         * The callable object must be invocable with GLFWwindow* and int arguments.
         *
         * @tparam F The type of the callable object.
         * @param callback The callable object to be stored as the callback function.
         */
        template<typename F>
        requires std::invocable<F, GLFWwindow *, int>
        GlfwWindowFocusCallbackFunction(F &&callback) : _callback(callback) {}

        /**
         * @brief Destructor for the GlfwWindowFocusCallbackFunction class.
         */
        ~GlfwWindowFocusCallbackFunction() {}

        static GlfwWindowFocusCallbackFunction *_instance;                      /**< The instance of the GlfwWindowFocusCallbackFunction class. */
        std::function<void(GLFWwindow *, int)> _callback;                       /**< The callback function to be called when the window focus changes. */
};

/**
 * @class GlfwWindowLostFocusCallbackFunction
 * @brief Represents a callback function for the GLFW window lost focus event.
 *
 * This class provides a mechanism to register a callback function that will be called when a GLFW window loses focus.
 * Only one instance of this class can exist at a time, and it follows the singleton design pattern.
 * The callback function must be invocable with parameters GLFWwindow* and int.
 */
class GlfwWindowLostFocusCallbackFunction {
    public:

        /**
         * @brief Deleted copy constructor.
         */
        GlfwWindowLostFocusCallbackFunction(const GlfwWindowLostFocusCallbackFunction &) = delete;

        /**
         * @brief Deleted copy assignment operator.
         */
        GlfwWindowLostFocusCallbackFunction &operator=(const GlfwWindowLostFocusCallbackFunction &) = delete;

        /**
         * @brief Get the singleton instance of the callback function.
         *
         * If the instance does not exist, it will be created with the provided callback function.
         * If the instance already exists and the 'force' parameter is set to true, the existing instance will be deleted and a new one will be created.
         *
         * @tparam F The type of the callback function.
         * @param callback The callback function to be registered.
         * @param force Whether to force the creation of a new instance even if one already exists.
         * @return The singleton instance of the callback function.
         */
        template<typename F>
        static GlfwWindowLostFocusCallbackFunction *getInstance(F &&callback, bool force = false)
        {
            if constexpr(std::invocable<F, GLFWwindow *, int>) {
                if (force && _instance) {
                    delete _instance;
                    _instance = nullptr;
                }
                if (!_instance)
                    _instance = new GlfwWindowLostFocusCallbackFunction(callback);
            }
            return _instance;
        }

        /**
         * @brief Get the singleton instance of the callback function.
         *
         * @return The singleton instance of the callback function.
         */
        static GlfwWindowLostFocusCallbackFunction *getInstance()
        {
            return _instance;
        }

        /**
         * @brief Call the callback function with the provided arguments.
         *
         * If the callback function is valid, it will be called with the provided arguments.
         *
         * @tparam _ArgTypes The types of the arguments.
         * @param args The arguments to be passed to the callback function.
         */
        template<typename... _ArgTypes>
        void call(_ArgTypes... args)
        {
            if (this->_callback)
                this->_callback(args...);
        }
    private:
        /**
         * @brief Private constructor.
         *
         * This constructor is only accessible by the getInstance() function.
         *
         * @tparam F The type of the callback function.
         * @param callback The callback function to be registered.
         */
        template<typename F>
        requires std::invocable<F, GLFWwindow *, int>
        GlfwWindowLostFocusCallbackFunction(F &&callback) : _callback(callback) {}

        /**
         * @brief Destructor.
         *
         * The destructor is private to prevent direct deletion of the instance.
         */
        ~GlfwWindowLostFocusCallbackFunction() {}

        static GlfwWindowLostFocusCallbackFunction *_instance;                  /**< The singleton instance of the callback function. */
        std::function<void(GLFWwindow *, int)> _callback;                       /**< The callback function to be called when the window loses focus. */
};

/**
 * @class GlfwWindowFileDropCallbackFunction
 * @brief Represents a singleton callback function for handling file drop events in a GLFW window.
 *
 * The GlfwWindowFileDropCallbackFunction class provides a singleton instance of a callback function
 * that can be used to handle file drop events in a GLFW window. It ensures that only one instance of
 * the callback function exists at a time.
 */
class GlfwWindowFileDropCallbackFunction {
    public:
        /**
         * @brief Deleted copy constructor.
         */
        GlfwWindowFileDropCallbackFunction(const GlfwWindowFileDropCallbackFunction &) = delete;

        /**
         * @brief Deleted copy assignment operator.
         */
        GlfwWindowFileDropCallbackFunction &operator=(const GlfwWindowFileDropCallbackFunction &) = delete;

        /**
         * @brief Get the singleton instance of the GlfwWindowFileDropCallbackFunction.
         *
         * If the instance does not exist, it will be created with the provided callback function.
         * If the instance already exists and the 'force' parameter is set to true, the existing instance will be deleted and a new one will be created.
         *
         * @tparam F The type of the callback function.
         * @param callback The callback function to be registered.
         * @param force Whether to force the creation of a new instance even if one already exists.
         * @return The singleton instance of the GlfwWindowFileDropCallbackFunction.
         */
        template<typename F>
        static GlfwWindowFileDropCallbackFunction *getInstance(F &&callback, bool force = false)
        {
            if constexpr(std::invocable<F, GLFWwindow *, int, const char*[]>) {
                if (force && _instance) {
                    delete _instance;
                    _instance = nullptr;
                }
                if (!_instance)
                    _instance = new GlfwWindowFileDropCallbackFunction(callback);
            }
            return _instance;
        }

        /**
         * @brief Get the singleton instance of the GlfwWindowFileDropCallbackFunction.
         *
         * @return The singleton instance of the GlfwWindowFileDropCallbackFunction.
         */
        static GlfwWindowFileDropCallbackFunction *getInstance()
        {
            return _instance;
        }

        /**
         * @brief Call the callback function with the provided arguments.
         *
         * If the callback function is valid, it will be called with the provided arguments.
         *
         * @tparam _ArgTypes The types of the arguments.
         * @param args The arguments to be passed to the callback function.
         */
        template<typename... _ArgTypes>
        void call(_ArgTypes... args)
        {
            if (this->_callback)
                this->_callback(args...);
        }
    private:
        /**
         * @brief Private constructor.
         *
         * This constructor is only accessible by the getInstance() function.
         *
         * @tparam F The type of the callback function.
         * @param callback The callback function to be registered.
         */
        template<typename F>
        requires std::invocable<F, GLFWwindow *, int, const char*[]>
        GlfwWindowFileDropCallbackFunction(F &&callback) : _callback(callback) {}

        /**
         * @brief Destructor.
         *
         * The destructor is private to prevent direct deletion of the instance.
         */
        ~GlfwWindowFileDropCallbackFunction() {}

        static GlfwWindowFileDropCallbackFunction *_instance;                   /**< The singleton instance of the callback function. */
        std::function<void(GLFWwindow *, int, const char*[])> _callback;        /**< The callback function to be called when a file is dropped into the window. */
};

/**
 * @class GlfwWindowKeyCallbackFunction
 * @brief Represents a singleton callback function for handling key events in a GLFW window.
 *
 * The GlfwWindowKeyCallbackFunction class provides a singleton instance of a callback function
 * that can be used to handle key events in a GLFW window. It ensures that only one instance of
 * the callback function exists at a time.
 */
class GlfwWindowScrollCallbackFunction {
    public:
        /**
         * @brief Deleted copy constructor.
         */
        GlfwWindowScrollCallbackFunction(const GlfwWindowScrollCallbackFunction &) = delete;

        /**
         * @brief Deleted copy assignment operator.
         */
        GlfwWindowScrollCallbackFunction &operator=(const GlfwWindowScrollCallbackFunction &) = delete;

        /**
         * @brief Get the singleton instance of the GlfwWindowScrollCallbackFunction.
         *
         * If the instance does not exist, it will be created with the provided callback function.
         * If the instance already exists and the 'force' parameter is set to true, the existing instance will be deleted and a new one will be created.
         *
         * @tparam F The type of the callback function.
         * @param callback The callback function to be registered.
         * @param force Whether to force the creation of a new instance even if one already exists.
         * @return The singleton instance of the GlfwWindowScrollCallbackFunction.
         */
        template<typename F>
        static GlfwWindowScrollCallbackFunction *getInstance(F &&callback, bool force = false)
        {
            if constexpr(std::invocable<F, GLFWwindow *, double, double>) {
                if (force && _instance) {
                    delete _instance;
                    _instance = nullptr;
                }
                if (!_instance)
                    _instance = new GlfwWindowScrollCallbackFunction(callback);
            }
            return _instance;
        }

        /**
         * @brief Get the singleton instance of the GlfwWindowScrollCallbackFunction.
         *
         * @return The singleton instance of the GlfwWindowScrollCallbackFunction.
         */
        static GlfwWindowScrollCallbackFunction *getInstance()
        {
            return _instance;
        }

        /**
         * @brief Call the callback function with the provided arguments.
         *
         * If the callback function is valid, it will be called with the provided arguments.
         *
         * @tparam _ArgTypes The types of the arguments.
         * @param args The arguments to be passed to the callback function.
         */
        template<typename... _ArgTypes>
        void call(_ArgTypes... args)
        {
            if (this->_callback)
                this->_callback(args...);
        }
    private:
        /**
         * @brief Private constructor.
         *
         * This constructor is only accessible by the getInstance() function.
         *
         * @tparam F The type of the callback function.
         * @param callback The callback function to be registered.
         */
        template<typename F>
        requires std::invocable<F, GLFWwindow *, double, double>
        GlfwWindowScrollCallbackFunction(F &&callback) : _callback(callback) {}

        /**
         * @brief Destructor.
         *
         * The destructor is private to prevent direct deletion of the instance.
         */
        ~GlfwWindowScrollCallbackFunction() {}

        static GlfwWindowScrollCallbackFunction *_instance;                     /**< The singleton instance of the callback function. */
        std::function<void(GLFWwindow *, double, double)> _callback;            /**< The callback function to be called when the mouse wheel is scrolled. */
};

/**
 * @class GlfwWindowKeyCallbackFunction
 * @brief Represents a singleton callback function for handling key events in a GLFW window.
 *
 * The GlfwWindowKeyCallbackFunction class provides a singleton instance of a callback function
 * that can be used to handle key events in a GLFW window. It ensures that only one instance of
 * the callback function exists at a time.
 */
class GlfwWindowContentScaleChangedCallbackFunction {
    public:
        /**
         * @brief Deleted copy constructor.
         */
        GlfwWindowContentScaleChangedCallbackFunction(const GlfwWindowContentScaleChangedCallbackFunction &) = delete;

        /**
         * @brief Deleted copy assignment operator.
         */
        GlfwWindowContentScaleChangedCallbackFunction &operator=(const GlfwWindowContentScaleChangedCallbackFunction &) = delete;

        /**
         * @brief Get the singleton instance of the GlfwWindowContentScaleChangedCallbackFunction.
         *
         * If the instance does not exist, it will be created with the provided callback function.
         * If the instance already exists and the 'force' parameter is set to true, the existing instance will be deleted and a new one will be created.
         *
         * @tparam F The type of the callback function.
         * @param callback The callback function to be registered.
         * @param force Whether to force the creation of a new instance even if one already exists.
         * @return The singleton instance of the GlfwWindowContentScaleChangedCallbackFunction.
         */
        template<typename F>
        static GlfwWindowContentScaleChangedCallbackFunction *getInstance(F &&callback, bool force = false)
        {
            if constexpr(std::invocable<F, GLFWwindow *, float, float>) {
                if (force && _instance) {
                    delete _instance;
                    _instance = nullptr;
                }
                if (!_instance)
                    _instance = new GlfwWindowContentScaleChangedCallbackFunction(callback);
            }
            return _instance;
        }

        /**
         * @brief Get the singleton instance of the GlfwWindowContentScaleChangedCallbackFunction.
         *
         * @return The singleton instance of the GlfwWindowContentScaleChangedCallbackFunction.
         */
        static GlfwWindowContentScaleChangedCallbackFunction *getInstance()
        {
            return _instance;
        }

        /**
         * @brief Call the callback function with the provided arguments.
         *
         * If the callback function is valid, it will be called with the provided arguments.
         *
         * @tparam _ArgTypes The types of the arguments.
         * @param args The arguments to be passed to the callback function.
         */
        template<typename... _ArgTypes>
        void call(_ArgTypes... args)
        {
            if (this->_callback)
                this->_callback(args...);
        }
    private:
        /**
         * @brief Private constructor.
         *
         * This constructor is only accessible by the getInstance() function.
         *
         * @tparam F The type of the callback function.
         * @param callback The callback function to be registered.
         */
        template<typename F>
        requires std::invocable<F, GLFWwindow *, float, float>
        GlfwWindowContentScaleChangedCallbackFunction(F &&callback) : _callback(callback) {}

        /**
         * @brief Destructor.
         *
         * The destructor is private to prevent direct deletion of the instance.
         */
        ~GlfwWindowContentScaleChangedCallbackFunction() {}

        static GlfwWindowContentScaleChangedCallbackFunction *_instance;        /**< The singleton instance of the callback function. */
        std::function<void(GLFWwindow *, float, float)> _callback;              /**< The callback function to be called when the content scale of the window changes. */
};

/**
 * @class GlfwWindowKeyCallbackFunction
 * @brief Represents a singleton callback function for handling key events in a GLFW window.
 *
 * The GlfwWindowKeyCallbackFunction class provides a singleton instance of a callback function
 * that can be used to handle key events in a GLFW window. It ensures that only one instance of
 * the callback function exists at a time.
 */
class GlfwWindowFramebufferResizedCallbackFunction {
    public:
        /**
         * @brief Deleted copy constructor.
         */
        GlfwWindowFramebufferResizedCallbackFunction(const GlfwWindowFramebufferResizedCallbackFunction &) = delete;

        /**
         * @brief Deleted copy assignment operator.
         */
        GlfwWindowFramebufferResizedCallbackFunction &operator=(const GlfwWindowFramebufferResizedCallbackFunction &) = delete;

        /**
         * @brief Get the singleton instance of the GlfwWindowFramebufferResizedCallbackFunction.
         *
         * If the instance does not exist, it will be created with the provided callback function.
         * If the instance already exists and the 'force' parameter is set to true, the existing instance will be deleted and a new one will be created.
         *
         * @tparam F The type of the callback function.
         * @param callback The callback function to be registered.
         * @param force Whether to force the creation of a new instance even if one already exists.
         * @return The singleton instance of the GlfwWindowFramebufferResizedCallbackFunction.
         */
        template<typename F>
        static GlfwWindowFramebufferResizedCallbackFunction *getInstance(F &&callback, bool force = false)
        {
            if constexpr(std::invocable<F, GLFWwindow *, int, int>) {
                if (force && _instance) {
                    delete _instance;
                    _instance = nullptr;
                }
                if (!_instance)
                    _instance = new GlfwWindowFramebufferResizedCallbackFunction(callback);
            }
            return _instance;
        }

        /**
         * @brief Get the singleton instance of the GlfwWindowFramebufferResizedCallbackFunction.
         *
         * @return The singleton instance of the GlfwWindowFramebufferResizedCallbackFunction.
         */
        static GlfwWindowFramebufferResizedCallbackFunction *getInstance()
        {
            return _instance;
        }

        /**
         * @brief Call the callback function with the provided arguments.
         *
         * If the callback function is valid, it will be called with the provided arguments.
         *
         * @tparam _ArgTypes The types of the arguments.
         * @param args The arguments to be passed to the callback function.
         */
        template<typename... _ArgTypes>
        void call(_ArgTypes... args)
        {
            if (this->_callback)
                this->_callback(args...);
        }
    private:
        /**
         * @brief Private constructor.
         *
         * This constructor is only accessible by the getInstance() function.
         *
         * @tparam F The type of the callback function.
         * @param callback The callback function to be registered.
         */
        template<typename F>
        requires std::invocable<F, GLFWwindow *, int, int>
        GlfwWindowFramebufferResizedCallbackFunction(F &&callback) : _callback(callback) {}

        /**
         * @brief Destructor.
         *
         * The destructor is private to prevent direct deletion of the instance.
         */
        ~GlfwWindowFramebufferResizedCallbackFunction() {}

        static GlfwWindowFramebufferResizedCallbackFunction *_instance;         /**< The singleton instance of the callback function. */
        std::function<void(GLFWwindow *, int, int)> _callback;                  /**< The callback function to be called when the framebuffer of the window is resized. */
};

/**
 * @class GlfwWindowKeyCallbackFunction
 * @brief Represents a singleton callback function for handling key events in a GLFW window.
 *
 * The GlfwWindowKeyCallbackFunction class provides a singleton instance of a callback function
 * that can be used to handle key events in a GLFW window. It ensures that only one instance of
 * the callback function exists at a time.
 */
class GlfwWindowIconifiedCallbackFunction {
    public:
        /**
         * @brief Deleted copy constructor.
         */
        GlfwWindowIconifiedCallbackFunction(const GlfwWindowIconifiedCallbackFunction &) = delete;

        /**
         * @brief Deleted copy assignment operator.
         */
        GlfwWindowIconifiedCallbackFunction &operator=(const GlfwWindowIconifiedCallbackFunction &) = delete;

        /**
         * @brief Get the singleton instance of the GlfwWindowIconifiedCallbackFunction.
         *
         * If the instance does not exist, it will be created with the provided callback function.
         * If the instance already exists and the 'force' parameter is set to true, the existing instance will be deleted and a new one will be created.
         *
         * @tparam F The type of the callback function.
         * @param callback The callback function to be registered.
         * @param force Whether to force the creation of a new instance even if one already exists.
         * @return The singleton instance of the GlfwWindowIconifiedCallbackFunction.
         */
        template<typename F>
        static GlfwWindowIconifiedCallbackFunction *getInstance(F &&callback, bool force = false)
        {
            if constexpr(std::invocable<F, GLFWwindow *, int>) {
                if (force && _instance) {
                    delete _instance;
                    _instance = nullptr;
                }
                if (!_instance)
                    _instance = new GlfwWindowIconifiedCallbackFunction(callback);
            }
            return _instance;
        }

        /**
         * @brief Get the singleton instance of the GlfwWindowIconifiedCallbackFunction.
         *
         * @return The singleton instance of the GlfwWindowIconifiedCallbackFunction.
         */
        static GlfwWindowIconifiedCallbackFunction *getInstance()
        {
            return _instance;
        }

        /**
         * @brief Call the callback function with the provided arguments.
         *
         * If the callback function is valid, it will be called with the provided arguments.
         *
         * @tparam _ArgTypes The types of the arguments.
         * @param args The arguments to be passed to the callback function.
         */
        template<typename... _ArgTypes>
        void call(_ArgTypes... args)
        {
            if (this->_callback)
                this->_callback(args...);
        }
    private:
        /**
         * @brief Private constructor.
         *
         * This constructor is only accessible by the getInstance() function.
         *
         * @tparam F The type of the callback function.
         * @param callback The callback function to be registered.
         */
        template<typename F>
        requires std::invocable<F, GLFWwindow *, int>
        GlfwWindowIconifiedCallbackFunction(F &&callback) : _callback(callback) {}

        /**
         * @brief Destructor.
         *
         * The destructor is private to prevent direct deletion of the instance.
         */
        ~GlfwWindowIconifiedCallbackFunction() {}

        static GlfwWindowIconifiedCallbackFunction *_instance;                  /**< The singleton instance of the callback function. */
        std::function<void(GLFWwindow *, int)> _callback;                       /**< The callback function to be called when the window is iconified or restored. */
};

/**
 * @class GlfwWindowKeyCallbackFunction
 * @brief Represents a singleton callback function for handling key events in a GLFW window.
 *
 * The GlfwWindowKeyCallbackFunction class provides a singleton instance of a callback function
 * that can be used to handle key events in a GLFW window. It ensures that only one instance of
 * the callback function exists at a time.
 */
class GlfwWindowMaximizedCallbackFunction {
    public:
        /**
         * @brief Deleted copy constructor.
         */
        GlfwWindowMaximizedCallbackFunction(const GlfwWindowMaximizedCallbackFunction &) = delete;

        /**
         * @brief Deleted copy assignment operator.
         */
        GlfwWindowMaximizedCallbackFunction &operator=(const GlfwWindowMaximizedCallbackFunction &) = delete;

        /**
         * @brief Get the singleton instance of the GlfwWindowMaximizedCallbackFunction.
         *
         * If the instance does not exist, it will be created with the provided callback function.
         * If the instance already exists and the 'force' parameter is set to true, the existing instance will be deleted and a new one will be created.
         *
         * @tparam F The type of the callback function.
         * @param callback The callback function to be registered.
         * @param force Whether to force the creation of a new instance even if one already exists.
         * @return The singleton instance of the GlfwWindowMaximizedCallbackFunction.
         */
        template<typename F>
        static GlfwWindowMaximizedCallbackFunction *getInstance(F &&callback, bool force = false)
        {
            if constexpr(std::invocable<F, GLFWwindow *, int>) {
                if (force && _instance) {
                    delete _instance;
                    _instance = nullptr;
                }
                if (!_instance)
                    _instance = new GlfwWindowMaximizedCallbackFunction(callback);
            }
            return _instance;
        }

        /**
         * @brief Get the singleton instance of the GlfwWindowMaximizedCallbackFunction.
         *
         * @return The singleton instance of the GlfwWindowMaximizedCallbackFunction.
         */
        static GlfwWindowMaximizedCallbackFunction *getInstance()
        {
            return _instance;
        }

        /**
         * @brief Call the callback function with the provided arguments.
         *
         * If the callback function is valid, it will be called with the provided arguments.
         *
         * @tparam _ArgTypes The types of the arguments.
         * @param args The arguments to be passed to the callback function.
         */
        template<typename... _ArgTypes>
        void call(_ArgTypes... args)
        {
            if (this->_callback)
                this->_callback(args...);
        }
    private:
        /**
         * @brief Private constructor.
         *
         * This constructor is only accessible by the getInstance() function.
         *
         * @tparam F The type of the callback function.
         * @param callback The callback function to be registered.
         */
        template<typename F>
        requires std::invocable<F, GLFWwindow *, int>
        GlfwWindowMaximizedCallbackFunction(F &&callback) : _callback(callback) {}

        /**
         * @brief Destructor.
         *
         * The destructor is private to prevent direct deletion of the instance.
         */
        ~GlfwWindowMaximizedCallbackFunction() {}

        static GlfwWindowMaximizedCallbackFunction *_instance;                  /**< The singleton instance of the callback function. */
        std::function<void(GLFWwindow *, int)> _callback;                       /**< The callback function to be called when the window is maximized or restored. */
};

/**
 * @class GlfwWindowKeyCallbackFunction
 * @brief Represents a singleton callback function for handling key events in a GLFW window.
 *
 * The GlfwWindowKeyCallbackFunction class provides a singleton instance of a callback function
 * that can be used to handle key events in a GLFW window. It ensures that only one instance of
 * the callback function exists at a time.
 */
class GlfwWindowMovedCallbackFunction {
    public:
        /**
         * @brief Deleted copy constructor.
         */
        GlfwWindowMovedCallbackFunction(const GlfwWindowMovedCallbackFunction &) = delete;

        /**
         * @brief Deleted copy assignment operator.
         */
        GlfwWindowMovedCallbackFunction &operator=(const GlfwWindowMovedCallbackFunction &) = delete;

        /**
         * @brief Get the singleton instance of the GlfwWindowMovedCallbackFunction.
         *
         * If the instance does not exist, it will be created with the provided callback function.
         * If the instance already exists and the 'force' parameter is set to true, the existing instance will be deleted and a new one will be created.
         *
         * @tparam F The type of the callback function.
         * @param callback The callback function to be registered.
         * @param force Whether to force the creation of a new instance even if one already exists.
         * @return The singleton instance of the GlfwWindowMovedCallbackFunction.
         */
        template<typename F>
        static GlfwWindowMovedCallbackFunction *getInstance(F &&callback, bool force = false)
        {
            if constexpr(std::invocable<F, GLFWwindow *, int, int>) {
                if (force && _instance) {
                    delete _instance;
                    _instance = nullptr;
                }
                if (!_instance)
                    _instance = new GlfwWindowMovedCallbackFunction(callback);
            }
            return _instance;
        }

        /**
         * @brief Get the singleton instance of the GlfwWindowMovedCallbackFunction.
         *
         * @return The singleton instance of the GlfwWindowMovedCallbackFunction.
         */
        static GlfwWindowMovedCallbackFunction *getInstance()
        {
            return _instance;
        }

        /**
         * @brief Call the callback function with the provided arguments.
         *
         * If the callback function is valid, it will be called with the provided arguments.
         *
         * @tparam _ArgTypes The types of the arguments.
         * @param args The arguments to be passed to the callback function.
         */
        template<typename... _ArgTypes>
        void call(_ArgTypes... args)
        {
            if (this->_callback)
                this->_callback(args...);
        }
    private:
        /**
         * @brief Private constructor.
         *
         * This constructor is only accessible by the getInstance() function.
         *
         * @tparam F The type of the callback function.
         * @param callback The callback function to be registered.
         */
        template<typename F>
        requires std::invocable<F, GLFWwindow *, int, int>
        GlfwWindowMovedCallbackFunction(F &&callback) : _callback(callback) {}

        /**
         * @brief Destructor.
         *
         * The destructor is private to prevent direct deletion of the instance.
         */
        ~GlfwWindowMovedCallbackFunction() {}

        static GlfwWindowMovedCallbackFunction *_instance;                      /**< The singleton instance of the callback function. */
        std::function<void(GLFWwindow *, int, int)> _callback;                  /**< The callback function to be called when the window is moved. */
};

/**
 * @class GlfwWindowKeyCallbackFunction
 * @brief Represents a singleton callback function for handling key events in a GLFW window.
 *
 * The GlfwWindowKeyCallbackFunction class provides a singleton instance of a callback function
 * that can be used to handle key events in a GLFW window. It ensures that only one instance of
 * the callback function exists at a time.
 */
class GlfwWindowResizedCallbackFunction {
    public:
        /**
         * @brief Deleted copy constructor.
         */
        GlfwWindowResizedCallbackFunction(const GlfwWindowResizedCallbackFunction &) = delete;

        /**
         * @brief Deleted copy assignment operator.
         */
        GlfwWindowResizedCallbackFunction &operator=(const GlfwWindowResizedCallbackFunction &) = delete;

        /**
         * @brief Get the singleton instance of the GlfwWindowResizedCallbackFunction.
         *
         * If the instance does not exist, it will be created with the provided callback function.
         * If the instance already exists and the 'force' parameter is set to true, the existing instance will be deleted and a new one will be created.
         *
         * @tparam F The type of the callback function.
         * @param callback The callback function to be registered.
         * @param force Whether to force the creation of a new instance even if one already exists.
         * @return The singleton instance of the GlfwWindowResizedCallbackFunction.
         */
        template<typename F>
        static GlfwWindowResizedCallbackFunction *getInstance(F &&callback, bool force = false)
        {
            if constexpr(std::invocable<F, GLFWwindow *, int, int>) {
                if (force && _instance) {
                    delete _instance;
                    _instance = nullptr;
                }
                if (!_instance)
                    _instance = new GlfwWindowResizedCallbackFunction(callback);
            }
            return _instance;
        }

        /**
         * @brief Get the singleton instance of the GlfwWindowResizedCallbackFunction.
         *
         * @return The singleton instance of the GlfwWindowResizedCallbackFunction.
         */
        static GlfwWindowResizedCallbackFunction *getInstance()
        {
            return _instance;
        }

        /**
         * @brief Call the callback function with the provided arguments.
         *
         * If the callback function is valid, it will be called with the provided arguments.
         *
         * @tparam _ArgTypes The types of the arguments.
         * @param args The arguments to be passed to the callback function.
         */
        template<typename... _ArgTypes>
        void call(_ArgTypes... args)
        {
            if (this->_callback)
                this->_callback(args...);
        }
    private:
        /**
         * @brief Private constructor.
         *
         * This constructor is only accessible by the getInstance() function.
         *
         * @tparam F The type of the callback function.
         * @param callback The callback function to be registered.
         */
        template<typename F>
        requires std::invocable<F, GLFWwindow *, int, int>
        GlfwWindowResizedCallbackFunction(F &&callback) : _callback(callback) {}

        /**
         * @brief Destructor.
         *
         * The destructor is private to prevent direct deletion of the instance.
         */
        ~GlfwWindowResizedCallbackFunction() {}

        static GlfwWindowResizedCallbackFunction *_instance;                    /**< The singleton instance of the callback function. */
        std::function<void(GLFWwindow *, int, int)> _callback;                  /**< The callback function to be called when the window is resized. */
};

/**
 * @class GlfwWindowKeyCallbackFunction
 * @brief Represents a singleton callback function for handling key events in a GLFW window.
 *
 * The GlfwWindowKeyCallbackFunction class provides a singleton instance of a callback function
 * that can be used to handle key events in a GLFW window. It ensures that only one instance of
 * the callback function exists at a time.
 */
class GlfwWindowRefreshedCallbackFunction {
    public:
        /**
         * @brief Deleted copy constructor.
         */
        GlfwWindowRefreshedCallbackFunction(const GlfwWindowRefreshedCallbackFunction &) = delete;

        /**
         * @brief Deleted copy assignment operator.
         */
        GlfwWindowRefreshedCallbackFunction &operator=(const GlfwWindowRefreshedCallbackFunction &) = delete;

        /**
         * @brief Get the singleton instance of the GlfwWindowRefreshedCallbackFunction.
         *
         * If the instance does not exist, it will be created with the provided callback function.
         * If the instance already exists and the 'force' parameter is set to true, the existing instance will be deleted and a new one will be created.
         *
         * @tparam F The type of the callback function.
         * @param callback The callback function to be registered.
         * @param force Whether to force the creation of a new instance even if one already exists.
         * @return The singleton instance of the GlfwWindowRefreshedCallbackFunction.
         */
        template<typename F>
        static GlfwWindowRefreshedCallbackFunction *getInstance(F &&callback, bool force = false)
        {
            if constexpr(std::invocable<F, GLFWwindow *>) {
                if (force && _instance) {
                    delete _instance;
                    _instance = nullptr;
                }
                if (!_instance)
                    _instance = new GlfwWindowRefreshedCallbackFunction(callback);
            }
            return _instance;
        }

        /**
         * @brief Get the singleton instance of the GlfwWindowRefreshedCallbackFunction.
         *
         * @return The singleton instance of the GlfwWindowRefreshedCallbackFunction.
         */
        static GlfwWindowRefreshedCallbackFunction *getInstance()
        {
            return _instance;
        }

        /**
         * @brief Call the callback function with the provided arguments.
         *
         * If the callback function is valid, it will be called with the provided arguments.
         *
         * @tparam _ArgTypes The types of the arguments.
         * @param args The arguments to be passed to the callback function.
         */
        template<typename... _ArgTypes>
        void call(_ArgTypes... args)
        {
            if (this->_callback)
                this->_callback(args...);
        }
    private:
        /**
         * @brief Private constructor.
         *
         * This constructor is only accessible by the getInstance() function.
         *
         * @tparam F The type of the callback function.
         * @param callback The callback function to be registered.
         */
        template<typename F>
        requires std::invocable<F, GLFWwindow *>
        GlfwWindowRefreshedCallbackFunction(F &&callback) : _callback(callback) {}

        /**
         * @brief Destructor.
         *
         * The destructor is private to prevent direct deletion of the instance.
         */
        ~GlfwWindowRefreshedCallbackFunction() {}

        static GlfwWindowRefreshedCallbackFunction *_instance;                  /**< The singleton instance of the callback function. */
        std::function<void(GLFWwindow *)> _callback;                            /**< The callback function to be called when the window is refreshed. */
};

/**
 * @class GlfwCursorCallbackFunction
 * @brief Represents a singleton callback function for GLFW window focus events.
 *
 * This class provides a singleton implementation for a callback function that is invoked when a GLFW window gains or loses focus.
 * It allows registering a callback function that takes a GLFWwindow pointer and an integer as arguments.
 * The callback function can be set using the `getInstance` method.
 * The `call` method is used to invoke the registered callback function.
 */
class GlfwCursorCallbackFunction {
    public:
        /**
         * @brief Deleted copy constructor.
         */
        GlfwCursorCallbackFunction(const GlfwCursorCallbackFunction &) = delete;

        /**
         * @brief Deleted copy assignment operator.
         */
        GlfwCursorCallbackFunction &operator=(const GlfwCursorCallbackFunction &) = delete;

        /**
         * Returns an instance of the GlfwCursorCallbackFunction with the specified callback function.
         *
         * @tparam F The type of the callback function.
         * @param callback The callback function to be invoked when the window focus changes.
         * @param force If set to true, forces the creation of a new instance even if one already exists.
         * @return A pointer to the instance of the GlfwCursorCallbackFunction.
         */
        template<typename F>
        static GlfwCursorCallbackFunction *getInstance(F &&callback, bool force = false)
        {
            if constexpr(std::invocable<F, GLFWwindow *, double, double>) {
                if (force && _instance) {
                    delete _instance;
                    _instance = nullptr;
                }
                if (!_instance)
                    _instance = new GlfwCursorCallbackFunction(callback);
            }
            return _instance;
        }

        /**
         * Returns the instance of the GlfwCursorCallbackFunction.
         *
         * @return A pointer to the instance of the GlfwCursorCallbackFunction.
         */
        static GlfwCursorCallbackFunction *getInstance()
        {
            return _instance;
        }

        /**
         * @brief Calls the callback function with the provided arguments.
         *
         * This function checks if a callback function is set and then calls it with the provided arguments.
         *
         * @tparam _ArgTypes The types of the arguments.
         * @param args The arguments to be passed to the callback function.
         */
        template<typename... _ArgTypes>
        void call(_ArgTypes... args)
        {
            if (this->_callback)
                this->_callback(args...);
        }
    private:
        /**
         * @brief Constructor for the GlfwCursorCallbackFunction class.
         *
         * This constructor takes a callable object as a parameter and initializes the _callback member variable.
         * The callable object must be invocable with GLFWwindow* and int arguments.
         *
         * @tparam F The type of the callable object.
         * @param callback The callable object to be stored as the callback function.
         */
        template<typename F>
        requires std::invocable<F, GLFWwindow *, double, double>
        GlfwCursorCallbackFunction(F &&callback) : _callback(callback) {}

        /**
         * @brief Destructor for the GlfwCursorCallbackFunction class.
         */
        ~GlfwCursorCallbackFunction() {}

        static GlfwCursorCallbackFunction *_instance;                      /**< The instance of the GlfwCursorCallbackFunction class. */
        std::function<void(GLFWwindow *, double, double)> _callback;                       /**< The callback function to be called when the window focus changes. */
};
