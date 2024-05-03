#pragma once
#include "../Game.hpp"
#include "Object2D.hpp"
#include "../Utilities.hpp"
#include "../Colorable.hpp"

/**
 * @brief Base clase for player and asteroids
 *
 */
class GameplayShape : public Object2D, public sf::ConvexShape, public Colorable
{
public:
    using Object2D::draw;
    sf::FloatRect getGlobalBounds() const { return rect; } // Overriden for the purpose
    virtual void setColorPalette(const ColorPalette &colorPalette) = 0;

    /**
     * @brief Get the collision point count for this object
     * (required for concave shapes, i.e. the player)
     *
     */
    virtual size_t getCollisionPointCount() { return this->getPointCount(); }

    /**
     * @brief Get the normalized axes of this shape
     *
     * @return std::vector<sf::Vector2f>
     */
    std::vector<sf::Vector2f> getAxes();

    sf::Vector2f getVelocity() const { return this->velocity; }
    void setVelocity(AsteroidMath::Vector2 v) { velocity = v; }

    /**
     * @brief Get the point of a gameplay shape that has been transformed.
     *
     * @param index Index of the point
     */
    sf::Vector2f getTransformedPoint(size_t index);

private:
    void onDraw(sf::RenderTarget &target, const sf::Transform &transform) const
    {
        rect = transform.transformRect(getLocalBounds());
        target.draw(*this, transform);
    }

protected:
    AsteroidMath::Vector2 velocity = AsteroidMath::Vector2::ZERO;
    mutable sf::FloatRect rect; // Need a custom rect class that can be transformed more easily.
};