#pragma once
#include "Object2D.hpp"
#include "../Utilities.hpp"
class Asteroid : public Object2D, public sf::ConvexShape
{
public:
    Asteroid();
    Asteroid(std::vector<sf::Vector2f> points, sf::Vector2f position);
    std::vector<sf::Vector2f> getNormals() {return normals;}
    sf::FloatRect getGlobalBounds()
    {
        return rect;
    }
private:
    mutable sf::FloatRect rect;
    std::vector<sf::Vector2f> normals;
    void update(float delta) override;
    void calculateNormals();
    void onDraw(sf::RenderTarget &target, const sf::Transform &transform) const
    {
        rect = transform.transformRect(getLocalBounds());
        target.draw(*this, transform);
    };
};