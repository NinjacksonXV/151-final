#pragma once
#include <queue>
#include "LoopingMusic.hpp"

class LoopingMusic;

class MusicHandler
{

public:
    MusicHandler(sf::InputSoundFile &starter);

    void queueUp(std::string &filename);
    void stopAll();

    void loopStarted();

private:
    LoopingMusic *primary;
    std::queue<LoopingMusic *> trackQueue;
    std::vector<LoopingMusic *> tracks;
};