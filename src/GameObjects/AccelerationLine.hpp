#include <list>
#include "GameplayShape.hpp"
#pragma once

class AccelerationLine : public GameplayShape
{
    public:
    AccelerationLine(sf::Vector2f position, sf::Vector2f angle);
    void update(float deltaTime) override;
    void setColorPalette(const ColorPalette &palette);
};
extern std::list<GameObject *> *gameObjectAccessor;
