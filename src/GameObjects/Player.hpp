#pragma once
#include "Object2D.hpp"

extern sf::RenderTarget const *windowAccessor;

class Player : public Object2D
{
private:
    void update(float delta) override;

public:
    void init() override;
};

// This can potentially move into the player class, unless we want to add some sort of destruction visual later. 
// Definitions are here temporarily. 
class PlayerShape : public Object2D
{
public:
    void init() override
    {
        shape.setPoint(0, {30, -10});
        shape.setPoint(1, {0, 0});
        shape.setPoint(2, {-30, -10});
        shape.setPoint(3, {0, 40});
        shape.setFillColor(sf::Color::Black);
        shape.setOutlineColor(sf::Color::White);
        shape.setOutlineThickness(4.0f);
    }

private:
    sf::ConvexShape shape{4};
    void onDraw(sf::RenderTarget &target, const sf::Transform &transform) const
    {
        target.draw(this->shape, transform);
    };
};

// TO-DO: Move this into its own header/compilation unit
/**
 * @brief This is the current star visual. It's essentially a rectangle that stays in the center of the screen, and takes in the player position to scroll 
 * the UV of a (relatively) simple star shader. It gives a nice effect, and is cheap to draw. 
 * 
 * Later, I'll update the shader so that it's possible to pass in the color palette. 
 * 
 */
class TempStars : public Object2D
{
public:
    // Window size values are hardcoded and should be redone.
    void init() override
    {
        sf::Vector2f winSize(windowAccessor->getSize().x, windowAccessor->getSize().y); 
        rect = sf::RectangleShape(winSize);
        // std::cout << windowAccessor->getSize().x << ", " << windowAccessor->getSize().y;
        if (!shader.loadFromFile("stars.frag", sf::Shader::Fragment))
            std::cout << "Didn't load shader\n";
        shader.setUniform("u_resolution", winSize);
        setOrigin({(winSize.x / 2.f), (winSize.y / 2.f)}); 

        renderState.shader = &shader;
    }

private:
    sf::RectangleShape rect;
    
    mutable sf::Shader shader;
    mutable sf::RenderStates renderState;

    // For now, this is a bit silly since it's being moved by the player every frame. I want to rewrite this later. 
    void onDraw(sf::RenderTarget &target, const sf::Transform &transform) const
    {
        // std::cout << this->getPosition().x << ", " << this->getPosition().y << "\n";
        shader.setUniform("position", sf::Vector2f(getPosition().x, getPosition().y  * -1.)); // SFML y-axis is inverted
        renderState.transform = this->getTransform();
        target.draw(rect, renderState);
    };
};