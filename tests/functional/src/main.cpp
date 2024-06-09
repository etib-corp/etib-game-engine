/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** main
*/

#include "tests.hpp"

#include "Sound/Device.hpp"
#include "Sound/Playlist.hpp"

int main()
{
    try {
        std::shared_ptr<EGE::Window> window = std::make_shared<EGE::Window>("Test", EGE::Maths::Vector2<int>(1920, 1080), EGE::Window::Styles::Titlebar | EGE::Window::Styles::Close);
        window->create();
        EGE::Sound::Device device;
        EGE::Sound::Playlist playlist("tests/assets/");
        std::string input;

        TestGUI *gui = new TestGUI();
        EGE::Color color(0.0f, 1.0f, 0.0f, 1.0f);

        gui->_menuBar->add(new EGE::Menu("File"), "file");
        gui->_menuBar->add(new EGE::Menu("Edit"), "edit");
        gui->_menuBar->add(new EGE::Menu("View"), "view");
        gui->_menuBar->add(new EGE::Menu("Help"), "help");

        gui->_panels["Main"]->add(new EGE::Button("Button", [](){std::cout << "PD" << std::endl;}), "button");
        gui->_panels["Main"]->add(new EGE::Text("Salut a tous bande de gentilles personnes..."), "text");

        EGE::Camera camera(EGE::Maths::Vector3<float>(6.0f, 0.0f, 6.0f), EGE::Maths::Vector3<float>(0.0f, 1.0f, 0.0f), -135.0f, 0.0f);
        EGE::Shader shader("./assets/shader/vertex.vert", "./assets/shader/fragment.frag");

        // EGE::Model player("./assets/models/vampire/dancing_vampire.dae");
        // EGE::Animation anim("./assets/models/vampire/dancing_vampire.dae", &player);
        // EGE::Model player("./assets/models/team1/player.dae");
        // EGE::Animation anim("./assets/models/team1/player.dae", &player);
        // EGE::Animator2000 animator(&anim);

        std::shared_ptr<EGE::Model> player = std::make_shared<EGE::Model>("./assets/models/backpack/backpack.obj", EGE::Maths::Vector3<float>(0.0f, 0.0f, 0.0f), EGE::Maths::Vector3<float>(0.0f, 0.0f, 0.0f), EGE::Maths::Vector3<float>(1.0f, 1.0f, 1.0f), true);
        std::shared_ptr<EGE::Model> player2 = std::make_shared<EGE::Model>("./assets/models/backpack/backpack.obj", EGE::Maths::Vector3<float>(5.0f, 0.0f, 0.0f), EGE::Maths::Vector3<float>(0.0f, 0.0f, 0.0f), EGE::Maths::Vector3<float>(1.0f, 1.0f, 1.0f), true);

        EGE::Movement movement(1000);
        movement.addModel("player", player);
        movement.addModel("player2", player2);

        movement.pushBackKeyFrame(EGE::Maths::Matrix<4, 4, float>({
            {0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f},
            {0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f}
        }))
        .pushBackKeyFrame(EGE::Maths::Matrix<4, 4, float>({
            {0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f},
            {0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f}
        }))
        .pushBackKeyFrame(EGE::Maths::Matrix<4, 4, float>({
            {0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f},
            {0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f}
        }))
        .pushBackKeyFrame(EGE::Maths::Matrix<4, 4, float>({
            {0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f},
            {0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f}
        }));


        window->bindTrigger(EGE::Event::Trigger(EGE::Event::Keyboard, EGE::Event::Key::KeyEscape, EGE::Event::Pressed, [&window]() {
            window->close();
        }));
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
            glfwSetCursorPos(window->getWindow(), window->getSize().x / 2, window->getSize().y / 2);
            float xoffset = xpos - window->getSize().x / 2;
            float yoffset = window->getSize().y / 2 - ypos;
            camera.rotate(xoffset, yoffset, true);
        });

        gui->init(window.get());

        float aspect = window->getSize().x / window->getSize().y;

        float deltaTime = 0.0f;
        float lastFrame = 0.0f;
        float lastTime = 0.0f;

        while (window->isOpen()) {
            float currentTime = glfwGetTime();
            deltaTime = currentTime - lastFrame;
            lastFrame = currentTime;
            // wait one second to dispaly the FPS
            if (currentTime - lastTime >= 1.0f) {
                std::cout << "FPS: " << 1 / deltaTime << std::endl;
                lastTime = currentTime;
            }

            // animator.updateAnimation(deltaTime);

            window->clear(color);
            gui->clear();

            shader.use();

            camera.update(shader, aspect);

            // auto transforms = animator.getFinalBoneMatrices();
            // for (int i = 0; i < transforms.size(); i++) {
                // shader.setMat("bones[" + std::to_string(i) + "]", EGE::Maths::Matrix<4, 4, float>(transforms[i]));
            // }
            movement.move(deltaTime);
            player->draw(shader);
            player2->draw(shader);
            gui->draw();
            gui->display();
            window->display();
            window->pollEvents();
        // playlist.play();
        // while (std::getline(std::cin, input)) {
        //     if (input == "next") {
        //         playlist.next();
        //     } else if (input == "previous") {
        //         playlist.previous();
        //     } else if (input == "pause") {
        //         playlist.pause();
        //     } else if (input == "play") {
        //         playlist.play();
        //     } else if (input == "stop") {
        //         playlist.stop();
        //     } else if (input == "exit") {
        //         break;
        //     }
        // }
        }
        return 0;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}