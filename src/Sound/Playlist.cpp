/*
** EPITECH PROJECT, 2024
** etib-game-engine
** File description:
** Playlist
*/

#include "Sound/Playlist.hpp"

EGE::Sound::Playlist::Playlist(const std::string &path)
{
    std::vector<std::string> mp3Files = Utils::getDirectoryFiles(path, ".mp3");

    for (const auto &file : mp3Files) {
        this->_musics.push_back(new EGE::Sound::Sound(file, EGE::Sound::Sound::FileType::MP3));
    }

    std::vector<std::string> wavFiles = Utils::getDirectoryFiles(path, ".wav");

    for (const auto &file : wavFiles) {
        this->_musics.push_back(new EGE::Sound::Sound(file, EGE::Sound::Sound::FileType::WAV));
    }

    this->_currentMusic = 0;
}

EGE::Sound::Playlist::~Playlist()
{
}

void EGE::Sound::Playlist::play()
{
    this->_musics[this->_currentMusic]->play();
}

void EGE::Sound::Playlist::pause()
{
    this->_musics[this->_currentMusic]->pause();
}

void EGE::Sound::Playlist::stop()
{
    this->_musics[this->_currentMusic]->stop();
    this->_currentMusic = 0;
}

void EGE::Sound::Playlist::next()
{
    this->_musics[this->_currentMusic]->stop();
    this->_currentMusic++;
    if (this->_currentMusic >= this->_musics.size())
        this->_currentMusic = 0;
    this->_musics[this->_currentMusic]->play();
}

void EGE::Sound::Playlist::previous()
{
    this->_musics[this->_currentMusic]->stop();
    this->_currentMusic = this->_currentMusic == 0 ? this->_musics.size() - 1 : this->_currentMusic - 1;
    this->_musics[this->_currentMusic]->play();
}
