#include "MusicHandler.hpp"

MusicHandler::MusicHandler(sf::InputSoundFile &starter)
{
    this->primary = new LoopingMusic(starter, this);
    this->primary->setLoop(true);
    this->primary->play();
    std::cout << "got here ";
}

void MusicHandler::queueUp(sf::InputSoundFile &track)
{
    LoopingMusic* newTrack = new LoopingMusic(track);
    tracks.push_back(newTrack);
    trackQueue.push(newTrack);
}

void MusicHandler::loopStarted()
{
    if (trackQueue.empty()) return;
    LoopingMusic* playedTrack = trackQueue.front();
    trackQueue.pop();
    playedTrack->setLoop(true);
    playedTrack->play();
    std::cout << "Track looped\n";
}