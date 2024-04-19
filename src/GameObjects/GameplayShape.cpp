#include "GameplayShape.hpp"

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
