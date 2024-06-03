/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** main
*/

#include "tests.hpp"

int main()
{
    try {
        // make a EGE init funciton so there is no more than one call to glfwInit and it can be usefull later
        std::shared_ptr<EGE::Window> window = std::make_shared<EGE::Window>("Test", EGE::Maths::Vector2<int>(1920, 1080), EGE::Window::Styles::Titlebar | EGE::Window::Styles::Close);
        window->create();
        EGE::Color color(1.0f, 0.0f, 0.0f, 1.0f);
        window->bindTrigger(EGE::Event::Trigger(EGE::Event::Keyboard, EGE::Event::Key::KeyEscape, EGE::Event::Pressed, [&window]() {
            window->close();
        }));
        glEnable(GL_DEPTH_TEST);
        TestGUI *gui = new TestGUI();

        gui->_menuBar->add(new EGE::Menu("File"));
        gui->_menuBar->add(new EGE::Menu("Edit"));
        gui->_menuBar->add(new EGE::Menu("View"));
        gui->_menuBar->add(new EGE::Menu("Help"));

        gui->_panels.at(0)->add(new EGE::Button("Button", [](){std::cout << "PD" << std::endl;}));
        gui->_panels.at(0)->add(new EGE::Text("Salut a tous bande de gentilles personnes..."));

        gui->init(window.get());

        EGE::Camera camera(EGE::Maths::Vector3<float>(6.0f, 0.0f, 6.0f), EGE::Maths::Vector3<float>(0.0f, 1.0f, 0.0f), -135.0f, 0.0f);
        EGE::Shader shader("/home/neisan/ETIB/etib-game-engine/assets/shader/vertex.vert", "/home/neisan/ETIB/etib-game-engine/assets/shader/fragment.frag");

        window->bindTrigger(EGE::Event::Trigger(EGE::Event::Keyboard, EGE::Event::Key::KeyW, EGE::Event::Pressed, [&camera]() {
            camera.move(EGE::Camera::FORWARD, 0.1f);
        }));
        window->bindTrigger(EGE::Event::Trigger(EGE::Event::Keyboard, EGE::Event::Key::KeyS, EGE::Event::Pressed, [&camera]() {
            camera.move(EGE::Camera::BACKWARD, 0.1f);
        }));
        window->bindTrigger(EGE::Event::Trigger(EGE::Event::Keyboard, EGE::Event::Key::KeyA, EGE::Event::Pressed, [&camera]() {
            camera.move(EGE::Camera::LEFT, 0.1f);
        }));
        window->bindTrigger(EGE::Event::Trigger(EGE::Event::Keyboard, EGE::Event::Key::KeyD, EGE::Event::Pressed, [&camera]() {
            camera.move(EGE::Camera::RIGHT, 0.1f);
        }));
        window->bindTrigger(EGE::Event::Trigger(EGE::Event::Keyboard, EGE::Event::Key::KeyQ, EGE::Event::Pressed, [&camera]() {
            camera.move(EGE::Camera::UP, 0.1f);
        }));
        window->bindTrigger(EGE::Event::Trigger(EGE::Event::Keyboard, EGE::Event::Key::KeyE, EGE::Event::Pressed, [&camera]() {
            camera.move(EGE::Camera::DOWN, 0.1f);
        }));
        window->bindWindowTrigger<GLFWwindow *, double, double>(EGE::Event::WindowTrigger::WindowCursorMoved, [&camera, &window](GLFWwindow *glfwWindow, double xpos, double ypos) {
            // get the direction of the mouse and rotate the camera in the direction
            static double lastX = 0.0;
            static double lastY = 0.0;
            static bool firstMouse = true;
            if (firstMouse) {
                lastX = xpos;
                lastY = ypos;
                firstMouse = false;
            }
            double xoffset = xpos - lastX;
            double yoffset = lastY - ypos;
            lastX = xpos;
            lastY = ypos;
            camera.rotate(xoffset, yoffset, true);
            // glfwSetCursorPos(glfwWindow, window->getSize().x / 2, window->getSize().y / 2);
        });

        while (window->isOpen()) {
            window->clear(color);
            gui->clear();

            shader.use();
            glm::mat4 projection = glm::perspective(glm::radians(camera.getZoom()), static_cast<float>(window->getSize().x) / static_cast<float>(window->getSize().y), 0.1f, 100.0f);
            glm::mat4 view = camera.getViewMatrix().toGlm();
            shader.setMat("projection", EGE::Maths::Matrix<4, 4, float>(projection));
            shader.setMat("view", EGE::Maths::Matrix<4, 4, float>(view));

            glm::mat4 modelMat1 = glm::mat4(1.0f);
            modelMat1 = glm::translate(modelMat1, glm::vec3(-2.0f, 0.0f, 0.0f));
            modelMat1 = glm::scale(modelMat1, glm::vec3(1.0f, 1.0f, 1.0f));
            shader.setMat("model", EGE::Maths::Matrix<4, 4, float>(modelMat1));

            shader.use();
            glm::mat4 modelMat2 = glm::mat4(1.0f);
            modelMat2 = glm::translate(modelMat2, glm::vec3(2.0f, 0.0f, 0.0f));
            modelMat2 = glm::scale(modelMat2, glm::vec3(1.0f, 1.0f, 1.0f));
            shader.setMat("model", EGE::Maths::Matrix<4, 4, float>(modelMat2));

            shader.use();
            glm::mat4 modelMat3 = glm::mat4(1.0f);
            modelMat3 = glm::translate(modelMat3, glm::vec3(0.0f, 0.0f, 0.0f));
            modelMat3 = glm::scale(modelMat3, glm::vec3(0.1f, 0.1f, 0.1f));
            shader.setMat("model", EGE::Maths::Matrix<4, 4, float>(modelMat3));

            gui->draw();
            gui->display();
            window->display();
            window->pollEvents();
        }
        return 0;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}
