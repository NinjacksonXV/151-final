#pragma once
#include "GameplayShape.hpp"
#include "../Utilities.hpp"

extern sf::RenderTarget const *windowAccessor;

class Player : public GameplayShape
{
public:
    void init() override;

private:
    void update(float delta) override;
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
        shader.setUniform("position", sf::Vector2f(getPosition().x, getPosition().y * -1.)); // SFML y-axis is inverted
        renderState.transform = this->getTransform();
        target.draw(rect, renderState);
    };
};
