/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Playlist
*/

#pragma once

#include "Sound/Sound.hpp"

#include "Error.hpp"

#include "Utils.hpp"

#include <string>
#include <vector>

namespace EGE {
    namespace Sound {
        class Playlist {
            public:
                Playlist(const std::string &path);
                ~Playlist();

                void play();
                void pause();
                void stop();
                void next();
                void previous();

            protected:
                std::vector<EGE::Sound::Sound *> _musics;
                size_t _currentMusic;
        };
    }
}
