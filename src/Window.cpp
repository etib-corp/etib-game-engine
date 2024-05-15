/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Window
*/

#include "Window.hpp"

EGE::Window::Window(const std::string& title, const EGE::Maths::Vector2<int>& size, const std::uint8_t& style)
{
    this->_title = title;
    this->_size = size;
    this->_position = EGE::Maths::Vector2<int>(0, 0);
    this->_framerateLimit = 60;
    this->_cursorVisible = true;
    this->_active = true;
    this->_style = style;
    this->_initializeGlfw();
}

EGE::Window::~Window()
{
    this->destroy();
    _glfwInitializations--;
    if (_glfwInitializations == 0)
        glfwTerminate();
}

void EGE::Window::create()
{
    if (this->_style & Styles::Titlebar) {
        glfwWindowHint(GLFW_DECORATED, GL_TRUE);
    } else {
        glfwWindowHint(GLFW_DECORATED, GL_FALSE);
    }

    if (this->_style & Styles::Resize) {
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    } else {
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    }
    if (this->_style & Styles::Fullscreen) {
        this->_window = glfwCreateWindow(this->_mode->width, this->_mode->height, _title.c_str(), this->_monitor, nullptr);
    } else {
        this->_window = glfwCreateWindow(this->_size.x, this->_size.y, this->_title.c_str(), nullptr, nullptr);
    }

    if (!this->_window)
        throw WindowError("Failed to create GLFW window");

    this->_event = std::make_shared<EGE::Event>(EGE::Event(this->_window));

    if (this->_style & Styles::Close) {
        this->_event->bindWindowTrigger<GLFWwindow *>(EGE::Event::WindowTrigger::WindowClose, [this](GLFWwindow* win) {
            this->close();
        });
    } else {
        this->_event->bindWindowTrigger<GLFWwindow *>(EGE::Event::WindowTrigger::WindowClose, [this](GLFWwindow* win) {
            glfwSetWindowShouldClose(this->_window, GL_FALSE);
        });
    }

    glfwMakeContextCurrent(this->_window);

    glfwSetInputMode(this->_window, GLFW_STICKY_KEYS, GL_TRUE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSwapInterval(1);
}

void EGE::Window::destroy()
{
    if (this->_window)
        glfwDestroyWindow(this->_window);
    this->_window = nullptr;
}

void EGE::Window::clear(EGE::Color color)
{
    glClearColor(color.red, color.green, color.blue, color.alpha);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void EGE::Window::display()
{
    glfwSwapBuffers(this->_window);
}

void EGE::Window::pollEvents()
{
    glfwPollEvents();
    this->_event->pollEvents();
}

bool EGE::Window::isOpen()
{
    return !glfwWindowShouldClose(this->_window);
}

void EGE::Window::close()
{
    glfwSetWindowShouldClose(this->_window, GL_TRUE);
}

bool EGE::Window::bindTrigger(const EGE::Event::Trigger& trigger)
{
    return this->_event->bindTrigger(trigger);
}

void EGE::Window::unbindTrigger(const EGE::Event::Trigger& trigger)
{
    this->_event->unbindTrigger(trigger);
}

void EGE::Window::setTitle(const std::string &title)
{
    this->_title = title;
}

void EGE::Window::setSize(const int &width, const int &height)
{
    this->_size.x = width;
    this->_size.x = height;
}

void EGE::Window::setSize(const EGE::Maths::Vector2<int> &size)
{
    this->_size = size;
}

void EGE::Window::setPosition(const int &x, const int &y)
{
    this->_size.x = x;
    this->_size.x = y;
}

void EGE::Window::setPosition(const EGE::Maths::Vector2<int> &position)
{
    this->_position = position;
}

void EGE::Window::setFramerateLimit(const int &limit)
{
    this->_framerateLimit = limit;
}

void EGE::Window::setCursorVisible(bool visible)
{
    this->_cursorVisible = visible;
}

void EGE::Window::setActive(bool active)
{
    this->_active = active;
}

EGE::Maths::Vector2<int> EGE::Window::getPosition()
{
    return this->_position;
}

EGE::Maths::Vector2<int> EGE::Window::getSize()
{
    return this->_size;
}

EGE::Maths::Vector2<int> EGE::Window::getMousePosition()
{
    return EGE::Maths::Vector2<int>(0, 0);
}

void EGE::Window::_initializeGlfw()
{
    if (!glfwInit())
        throw WindowError("Failed to initialize GLFW");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwSetErrorCallback([](int error, const char* description) {
        std::string errorStr = std::to_string(error);
        throw WindowError("Error |" +  errorStr + "| : \n\t" + description);
    });

    glfwWindowHint(GLFW_SAMPLES, 4);

    glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);

    this->_monitor = glfwGetPrimaryMonitor();
    this->_mode = glfwGetVideoMode(this->_monitor);
    _glfwInitializations++;
}