#pragma once
#include "Object2D.hpp"
#include "../Utilities.hpp"
class Asteroid : public Object2D, public sf::ConvexShape
{
public:
    Asteroid();
    Asteroid(std::vector<sf::Vector2f> points, sf::Vector2f position);
    std::vector<sf::Vector2f> getNormals() {return normals;}

private:
    std::vector<sf::Vector2f> normals;
    void update(float delta) override;
    void calculateNormals();
    void onDraw(sf::RenderTarget &target, const sf::Transform &transform) const
    {
        target.draw(*this, transform);
    };
};