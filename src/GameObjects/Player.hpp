#pragma once
#include "GameplayShape.hpp"
#include "Bullet.hpp"
#include "AccelerationLine.hpp"
#include "../Utilities.hpp"

extern sf::View const *gameViewAccessor;
extern sf::RenderTarget const *windowAccessor;

class Player : public GameplayShape
{
public:
    Player();
    void init();
    void update(float delta);

    void setColorPalette(const ColorPalette &colorPalette);
    size_t getCollisionPointCount() override { return 3; };
    void collided(sf::Vector2f minTranslation, float magnitude);

    unsigned int getHP() { return this->impacts; }

    enum State
    {
        DEAD,
        INITIALIZING,
        PLAYING,
    } state = INITIALIZING;

private:
    void dieAnimation(float delta);
    bool deathState = false;
    unsigned int impacts = 3;
};

// TO-DO: Move this into its own header/compilation unit. Actually... this is never getting done. Hah.
/**
 * @brief This is the current star visual. It's essentially a rectangle that stays in the center of the screen, and takes in the player position to scroll
 * the UV of a (relatively) simple star shader. It gives a nice effect, and is cheap to draw.
 *
 */
class TempStars : public Object2D, public Colorable
{
public:
    void init() override
    {
        sf::Vector2f winSize(gameViewAccessor->getSize().x, gameViewAccessor->getSize().y);
        backgroundRect = sf::RectangleShape(winSize);
        starRect = sf::RectangleShape(winSize);
        if (!shader.loadFromFile("stars.frag", sf::Shader::Fragment))
            std::cout << "Didn't load shader\n";

        setColorPalette(Game::getColorPalette());

        shader.setUniform("u_resolution", winSize);

        this->setOrigin(this->starRect.getSize().x / 2.f, this->starRect.getSize().x / 2.f);
        renderState.shader = &shader;
    }
    void setColorPalette(const ColorPalette &colorPalette) override
    {
        backgroundRect.setFillColor(colorPalette.primary);
        // shader.setUniform("backgroundCol", sf::Glsl::Vec4(colorPalette.primary));
        shader.setUniform("starCol", sf::Glsl::Vec4(colorPalette.tertiary));
    }
    void updatePosition(sf::Vector2f delta)
    {
        shaderPos += delta;
    }

private:
    sf::RectangleShape starRect;
    mutable sf::RectangleShape backgroundRect;

    sf::Vector2f shaderPos;

    mutable sf::Shader shader;
    mutable sf::RenderStates renderState;

    void onDraw(sf::RenderTarget &target, const sf::Transform &transform) const
    {
        renderState.transform = this->getTransform(); // Hack because this doesn't inherit from drawable
        shader.setUniform("position", sf::Vector2f(shaderPos.x, shaderPos.y * -1.f));
        target.draw(backgroundRect, this->getTransform());
        target.draw(starRect, renderState);
    };
};
