#include <vector>
#include <SFML/Graphics.hpp>
#include "GameObjects/GameObject.hpp"

enum CollisionLayer
{
    C_Player,
    C_Asteroid,
    C_Projectile
};

// This class is currently undeveloped. I'll come back to this once I have a better idea of what's needed. 
class Game
{
public:
    Game();
    void GameLoop();
    void HandleCollision();
    static const sf::RenderWindow* const windowAccessor;

private:
    sf::RenderWindow m_window;


    std::vector<GameObject *> gameObjects;
    void HandleCleanup();
};
