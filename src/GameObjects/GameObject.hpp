#include <SFML/Graphics.hpp>
#pragma once

class GameObject
{
public:
    virtual void init() {}; // may be unnecessary?
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderTarget &target) const = 0;

private:
    sf::RenderTarget *renderTarget;
};
