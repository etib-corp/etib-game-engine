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
        std::string input;

        playlist.play();
        while (std::getline(std::cin, input)) {
            if (input == "next") {
                playlist.next();
            } else if (input == "previous") {
                playlist.previous();
            } else if (input == "pause") {
                playlist.pause();
            } else if (input == "play") {
                playlist.play();
            } else if (input == "stop") {
                playlist.stop();
            } else if (input == "exit") {
                break;
            }
        }
        return 0;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}