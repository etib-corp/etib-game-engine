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
        EGE::Sound::Device device;
        EGE::Sound::Playlist playlist("tests/assets/");

        playlist.play();
        while (true) {
            playlist.update();
        }
        return 0;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}