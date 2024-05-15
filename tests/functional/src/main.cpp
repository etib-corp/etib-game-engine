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
        std::shared_ptr<EGE::Window> window = std::make_shared<EGE::Window>("Test", EGE::Maths::Vector2<int>(1280, 720), EGE::Window::Styles::Titlebar | EGE::Window::Styles::Close);
        window->create();
        EGE::Color color(0.0f, 0.0f, 0.0f, 1.0f);
        float vertices[] = {
            0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,
            0.0f, 0.5f, 0.0f,     0.0f, 0.0f, 1.0f
        };
        window->bindTrigger(EGE::Event::Trigger(EGE::Event::Keyboard, EGE::Event::Key::KeyEscape, EGE::Event::Pressed, [&window]() {
            window->close();
        }));
        EGE::Shader shader("/home/julithein/delivery/etib/etib-game-engine/assets/shader/vertex.vert", "/home/julithein/delivery/etib/etib-game-engine/assets/shader/fragment.frag");
        unsigned int VBO;
        unsigned int VAO;

        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);


        while (window->isOpen()) {
            window->clear(color);

            // draw triangle
            shader.use();
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            // end the current frame

            window->pollEvents();
            window->display();
        }
        return 0;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}
