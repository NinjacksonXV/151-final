#include <vector>
#include <SFML/Graphics.hpp>
#include "GameObjects/GameObject.hpp"

// This class is currently undeveloped. I'll come back to this once I have a better idea of what's needed. 
class Game
{
public:
    Game();
    void GameLoop();
    static const sf::RenderWindow* const windowAccessor;

private:
    sf::RenderWindow m_window;


    std::vector<GameObject *> gameObjects;
    void HandleCleanup();
};
