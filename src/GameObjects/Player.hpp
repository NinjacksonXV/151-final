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
    void setColorPalette(const ColorPalette &colorPalette);
    // Since the player is a concave shape, we don't want to factor in
    // the interior point; it may cause minor inconsistencies, but likely
    // few and far between, where a very acute angle manages to squeeze
    // into the gap. Only possible if the player flys at a vertex and turns
    // 180 degrees and floats into it.
    std::size_t getPointCount() const override { return 3; }

private:
    void update(float delta) override;
    TempStars *stars;
};

// TO-DO: Move this into its own header/compilation unit
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
        shader.setUniform("backgroundCol", sf::Glsl::Vec4(colorPalette.primary));
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
