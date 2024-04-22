#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameObjects/GameObject.hpp"
#include "ColorPalette.hpp"

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
    void GameLoop();
    void HandleCollision();
    static const sf::RenderWindow *const windowAccessor;

    static ColorPalette getColorPalette() { return currentPalette; }
    static void setColorPalette(ColorPalette colorPalette){currentPalette = colorPalette;}

private:
    sf::RenderWindow m_window;
    std::vector<GameObject *> gameObjects;

    static ColorPalette currentPalette;

    void HandleCleanup();
};
