#include <vector>
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"

class Game
{
public:
    Game();
    void GameLoop();

private:
    sf::RenderWindow m_window;


    std::vector<GameObject *> gameObjects;
    void HandleCleanup();
};
