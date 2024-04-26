#pragma once
#include <SFML/Audio.hpp>
#include <iomanip>
#include <iostream>
#include <thread>
#include "MusicHandler.hpp"

class MusicHandler;

/**
 * @brief Reimplementation of Music for custom loop behavior
 * https://github.com/SFML/SFML/wiki/Source:-Looping-Music
 *
 */
class LoopingMusic : public sf::SoundSource
{
public:
    LoopingMusic(std::string &filename);
    void play();
    void pause();
    void stop();

private:
    sf::SoundBuffer audioBuffer;
    MusicHandler *musicHandler = nullptr;
};