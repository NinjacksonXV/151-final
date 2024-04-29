#include "GameplayShape.hpp"

std::vector<sf::Vector2f> GameplayShape::getAxes()
{
    std::vector<sf::Vector2f> axes;
    for (size_t i = 0; i < getCollisionPointCount(); i++)
    {
        sf::Vector2f p1 = Object2D::getTransform().transformPoint(getPoint(i));
        sf::Vector2f p2 = Object2D::getTransform().transformPoint(getPoint(i + 1 == getCollisionPointCount() ? 0 : i + 1));

        // sf::Vector2f p1 = this->getPoint(i);
        // sf::Vector2f p2 = getPoint(i + 1 == getCollisionPointCount() ? 0 : i + 1);

        sf::Vector2f edge = p1 - p2;

        sf::Vector2f normal = AsteroidMath::Vector2(edge.y * -1, edge.x).normalized();
        axes.push_back(normal);
    }
    return axes;
}

/**
 * @brief Duplicate of getAxes() from an old implementation. Deprecated.
 *
 */
void GameplayShape::calculateNormals()
{
    if (this->normals.capacity() != this->getPointCount())
    {
        this->normals.resize(this->getPointCount());
    }
    for (size_t i = 0; i < this->getPointCount(); i++)
    {
        sf::Vector2f p1 = this->getPoint(i); // I need a toGlobal() function for this and the one following.
        sf::Vector2f p2 = this->getPoint(i + 1 == this->getPointCount() ? 0 : i + 1);

        sf::Vector2f edge = p1 - p2;
        AsteroidMath::Vector2 normal = {edge.y * -1, edge.x};
        normal.normalize();
        this->normals[i] = normal;
        std::cout << i + 1 << ". " << normal << '\n';
    }
}

sf::Vector2f GameplayShape::getTransformedPoint(size_t index)
{
    return this->Object2D::getTransform().transformPoint(this->getPoint(index));
}
