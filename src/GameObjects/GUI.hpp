#pragma once
#include "GameObject.hpp"

extern sf::RenderTarget const *windowAccessor;

class GUI : public GameObject
{
    // static sf::Vector2 
    enum Positions
    {
        RIGHT,
        LEFT,
        TOP,
        BOTTOM,
        VERTICAL_CENTER,
        HORIZ_CENTER,
    }
    public:
        virtual void init();
        virtual void update() {};
        virtual void draw();
    void setPosition(Positions horizontalPosition, Positions verticalPosition, float hOffset, float vOffset);

    void normalizeScreenSpace(sf::Vector size)
    {

    }

};
