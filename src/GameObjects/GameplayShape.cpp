#include "GameplayShape.hpp"

std::vector<sf::Vector2f> GameplayShape::getAxes()
{
    std::vector<sf::Vector2f> axes;
    for (size_t i = 0; i < getCollisionPointCount(); i++)
    {
        sf::Vector2f p1 = getTransformedPoint(i);
        sf::Vector2f p2 = getTransformedPoint(i + 1 == getCollisionPointCount() ? 0 : i + 1);

        sf::Vector2f edge = p2 - p1;

        sf::Vector2f normal = AsteroidMath::Vector2(edge.y, -edge.x).normalized();
        axes.push_back(normal);
    }
    return axes;
}

sf::Vector2f GameplayShape::getTransformedPoint(size_t index)
{
    return this->Object2D::getTransform().transformPoint(this->getPoint(index));
}
