#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameObjects/GameObject.hpp"
#include "GameObjects/GameplayShape.hpp"
#include "ColorPalette.hpp"
#include "Colorable.hpp"

class Colorable;

enum CollisionLayer
{
    C_Player = 0x01,
    C_Asteroid = 0x02,
    C_Projectile = 0x04
};

// This class is currently undeveloped. I'll come back to this once I have a better idea of what's needed.
class Game
{
public:
    template <typename T>
    void registerObject(T *param)
    {
        if constexpr (std::is_base_of<Colorable, T>::value)
        {
            this->colorables.push_back(param);
        }
        if constexpr (std::is_base_of<GameObject, T>::value)
        {
            this->gameObjects.push_back(param);
        }
    }
    void GameLoop();
    void HandleCollision(CollisionLayer layer);
    static const sf::RenderWindow *const window;

    static ColorPalette getColorPalette() { return currentPalette; }
    static void setColorPalette(ColorPalette colorPalette) { currentPalette = colorPalette; }

private:
    sf::RenderWindow m_window;
    std::vector<GameObject *> gameObjects;

    static std::vector<Colorable *> colorables;
    static ColorPalette currentPalette;

    void HandleCleanup();
};
