#pragma once
#include "GameObject.hpp"
#include "Button.hpp"
#include "Display.hpp"

extern sf::RenderTarget const *windowAccessor;

class GUI : public GameObject
{
    enum Positions
    {
        RIGHT,
        LEFT,
        TOP,
        BOTTOM,
        VERTICAL_CENTER,
        HORIZ_CENTER
    };

    void addButton(sf::Vector2f position, sf::Text text, sf::Vector2f size);
    void addText(sf::Vector2f position, sf::Text text);


private:
    sf::Vector2f mPosition;
    std::vector<Button> buttons;
    std::vector<Display> displays;
};
