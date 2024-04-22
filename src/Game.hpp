#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameObjects/GameObject.hpp"
#include "GameObjects/GameplayShape.hpp"
#include "ColorPalette.hpp"
#include "Collision.hpp"

class Game
{
public:
    void GameLoop();
    void HandleCollision(CollisionLayer layer);
    static const sf::RenderWindow *const window;

    static ColorPalette getColorPalette() { return currentPalette; }
    static void setColorPalette(ColorPalette colorPalette){currentPalette = colorPalette;}

private:
    sf::RenderWindow m_window;
    std::vector<GameObject *> gameObjects;
    // std::vector<Collidable*> c_Player;
    // std::vector<Collidable*> c_Asteroid;
    // std::vector<Collidable*> c_Player;
    static ColorPalette currentPalette;

    void HandleCleanup();
};
