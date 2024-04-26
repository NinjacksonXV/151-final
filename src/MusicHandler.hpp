#pragma once
#include <queue>
#include "LoopingMusic.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
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
