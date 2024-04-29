#pragma once
#include "../Game.hpp"
#include "Object2D.hpp"
#include "../Utilities.hpp"
#include "../Colorable.hpp"

class GameplayShape : public Object2D, public sf::ConvexShape, public Colorable
{
public:
    using Object2D::draw;
    sf::FloatRect getGlobalBounds() { return rect; };
    virtual void setColorPalette(const ColorPalette &colorPalette) = 0;
    virtual size_t getCollisionPointCount() { return this->getPointCount();}

    std::vector<sf::Vector2f> getAxes();

    sf::Vector2f getVelocity() const {return this->velocity;}
    void calculateNormals();
    sf::Vector2f getTransformedPoint(size_t index);
private:
    std::vector<sf::Vector2f> normals;
    void onDraw(sf::RenderTarget &target, const sf::Transform &transform) const
    {
        rect = transform.transformRect(getLocalBounds());
        target.draw(*this, transform);
    }
protected:
    AsteroidMath::Vector2 velocity = AsteroidMath::Vector2::ZERO;
    mutable sf::FloatRect rect;
};