#pragma once
#include "GameplayShape.hpp"
#include "../Utilities.hpp"

extern sf::RenderTarget const *windowAccessor;
extern sf::View const *gameViewAccessor;

class TempStars;

class Player : public GameplayShape
{
public:
    void init() override;

private:
    void update(float delta) override;
    TempStars* stars;
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
        sf::Vector2f winSize(gameViewAccessor->getSize().x, gameViewAccessor->getSize().y);
        std::cout << winSize << '\n';
        rect = sf::RectangleShape(winSize);
        // std::cout << windowAccessor->getSize().x << ", " << windowAccessor->getSize().y;
        if (!shader.loadFromFile("stars.frag", sf::Shader::Fragment))
            std::cout << "Didn't load shader\n";
        shader.setUniform("u_resolution", winSize);
        setOrigin(this->rect.getSize().x / 2.f, this->rect.getSize().x / 2.f);

        renderState.shader = &shader;
    }
    void updatePosition(sf::Vector2f delta)
    {
        shaderPos += delta;
    }
private:
    sf::RectangleShape rect;

    sf::Vector2f shaderPos;

    mutable sf::Shader shader;
    mutable sf::RenderStates renderState;

    void onDraw(sf::RenderTarget &target, const sf::Transform &transform) const
    {
        renderState.transform = this->getTransform(); // Hack because this doesn't inherit from drawable
        shader.setUniform("position", sf::Vector2f(shaderPos.x, shaderPos.y * -1.f));
        target.draw(rect, renderState);
    };
};
