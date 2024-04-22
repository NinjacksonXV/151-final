#pragma once
#include "../Game.hpp"
#include "Object2D.hpp"
#include "../Utilities.hpp"
#include "../Colorable.hpp"

class GameplayShape : public Object2D, public sf::ConvexShape, public Colorable
{
public:
    sf::FloatRect getGlobalBounds() { return rect; };
    virtual void setColorPalette(ColorPalette colorPalette) = 0;
private:
    std::vector<sf::Vector2f> normals;
    std::vector<CollisionLayer> collisionLayers;
    void calculateNormals();
    void onDraw(sf::RenderTarget &target, const sf::Transform &transform) const
    {
        rect = transform.transformRect(getLocalBounds());
        target.draw(*this, transform);
    };

protected:
    mutable sf::FloatRect rect;

};