#include "Game.hpp"

void Game::GameLoop()
{
    sf::Clock clock;
    bool tempGameState = true; // replace this with game state machine logic later
    while (m_window.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        while (tempGameState)
        {
            for (GameObject *object : gameObjects)
            {
                object->update(deltaTime.asSeconds());
            }
        }
    }
}