/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** main
*/

#include "tests.hpp"

int main()
{
    std::shared_ptr<EGE::Window> window = std::make_shared<EGE::Window>("Test", EGE::Maths::Vector2<int>(1280, 720), EGE::Window::Styles::Titlebar | EGE::Window::Styles::Close);
    window->create();
    EGE::Color color(0.0f, 0.0f, 0.0f, 1.0f);
    window->bindTrigger(EGE::Event::Trigger(EGE::Event::Type::Keyboard, EGE::Event::Key::KeyEscape, EGE::Event::Mode::JustPressed, [&window]() {
        std::cout << "Window closed." << std::endl;
        window->close();
    }));

    window->bindWindowTrigger<GLFWwindow *>(EGE::Event::WindowTrigger::WindowClose, [](GLFWwindow * win) {
        std::cout << "Window not closed." << std::endl;
    });
    window->bindWindowTrigger<GLFWwindow *, int>(EGE::Event::WindowTrigger::WindowFocus, [](GLFWwindow *win, int focused) {
        std::cout << "Window focus" << std::endl;
    });
    window->bindWindowTrigger<GLFWwindow *, int>(EGE::Event::WindowTrigger::WindowLostFocus, [](GLFWwindow *win, int focused) {
        std::cout << "Window unfocused" << std::endl;
    });
    window->bindWindowTrigger<GLFWwindow *, int, const char *[]>(EGE::Event::WindowTrigger::WindowFileDrop, [](GLFWwindow *win, int count, const char **paths) {
        for (int i = 0; i < count; i++)
            std::cout << "File dropped: " << paths[i] << std::endl;
    });
    window->bindWindowTrigger<GLFWwindow *, double, double>(EGE::Event::WindowTrigger::WindowScroll, [&color](GLFWwindow *win, double xoffset, double yoffset) {
        if (yoffset > 0)
            color.red = std::clamp(color.red + 0.01f, 0.0f, 1.0f);
        else if (yoffset < 0)
            color.red = std::clamp(color.red - 0.01f, 0.0f, 1.0f);
        if (xoffset < 0)
            color.green = std::clamp(color.green + 0.01f, 0.0f, 1.0f);
        else if (xoffset > 0)
            color.green = std::clamp(color.green - 0.01f, 0.0f, 1.0f);
    });
    window->bindWindowTrigger<GLFWwindow *, float, float>(EGE::Event::WindowTrigger::WindowContentScaleChanged, [](GLFWwindow *win, float x, float y) {
        std::cout << "Window content scale changed to: " << x << ", " << y << std::endl;
    });
    window->bindWindowTrigger<GLFWwindow *, int, int>(EGE::Event::WindowTrigger::WindowFramebufferResized, [](GLFWwindow *win, int width, int height) {
        std::cout << "Window framebuffer resized to: " << width << ", " << height << std::endl;
    });
    window->bindWindowTrigger<GLFWwindow *, int, int>(EGE::Event::WindowTrigger::WindowMoved, [](GLFWwindow *win, int x, int y) {
        std::cout << "Window moved to: " << x << ", " << y << std::endl;
    });
    window->bindWindowTrigger<GLFWwindow *, int, int>(EGE::Event::WindowTrigger::WindowResized, [](GLFWwindow *win, int width, int height) {
        std::cout << "Window resized to: " << width << ", " << height << std::endl;
    });
    window->bindWindowTrigger<GLFWwindow *>(EGE::Event::WindowTrigger::WindowRefreshed, [](GLFWwindow *win) {
        std::cout << "Window refreshed." << std::endl;
    });
    while (window->isOpen()) {
        window->clear(color);
        window->pollEvents();
        window->display();
    }
    return 0;
}
