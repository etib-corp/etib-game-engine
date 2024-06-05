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
        EGE::Color color(0.0f, 1.0f, 0.0f, 1.0f);
        window->bindTrigger(EGE::Event::Trigger(EGE::Event::Keyboard, EGE::Event::Key::KeyEscape, EGE::Event::Pressed, [&window]() {
            window->close();
        }));
        TestGUI *gui = new TestGUI();

        gui->_menuBar->add(new EGE::Menu("File"), "file");
        gui->_menuBar->add(new EGE::Menu("Edit"), "edit");
        gui->_menuBar->add(new EGE::Menu("View"), "view");
        gui->_menuBar->add(new EGE::Menu("Help"), "help");

        gui->_panels["Main"]->add(new EGE::Button("Button", [](){std::cout << "PD" << std::endl;}), "button");
        gui->_panels["Main"]->add(new EGE::Text("Salut a tous bande de gentilles personnes..."), "text");

        EGE::Camera camera(EGE::Maths::Vector3<float>(6.0f, 0.0f, 6.0f), EGE::Maths::Vector3<float>(0.0f, 1.0f, 0.0f), -135.0f, 0.0f);
        EGE::Shader shader("./assets/shader/player.vert", "./assets/shader/fragment.frag");

        EGE::Model player("./assets/models/vampire/dancing_vampire.dae");
        EGE::Animation anim("./assets/models/vampire/dancing_vampire.dae", &player);
        // EGE::Model player("./assets/models/team1/player.dae");
        // EGE::Animation anim("./assets/models/team1/player.dae", &player);
        EGE::Animator2000 animator(&anim);

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
            camera.rotate(xoffset, yoffset, true);\
            // glfwSetCursorPos(glfwWindow, window->getSize().x / 2, window->getSize().y / 2);
        });

        gui->init(window.get());

        float aspect = window->getSize().x / window->getSize().y;

        float deltaTime = 0.0f;
        float lastFrame = 0.0f;

        while (window->isOpen()) {
            float currentTime = glfwGetTime();
            deltaTime = currentTime - lastFrame;
            lastFrame = currentTime;

            animator.updateAnimation(deltaTime);

            window->clear(color);
            gui->clear();

            shader.use();

            camera.update(shader, aspect);

            auto transforms = animator.getFinalBoneMatrices();
            for (int i = 0; i < transforms.size(); i++) {
                shader.setMat("bones[" + std::to_string(i) + "]", EGE::Maths::Matrix<4, 4, float>(transforms[i]));
            }
            player.draw(shader);
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