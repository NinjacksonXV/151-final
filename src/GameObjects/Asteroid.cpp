#include "Asteroid.hpp"


Asteroid::Asteroid(std::vector<sf::Vector2f> points, sf::Vector2f position)
{
    this->setPointCount(points.size());
    for (size_t i = 0; i < points.size(); i++)
    {
        setPoint(i, points[i]);
    }
    calculateNormals();
    this->Object2D::setPosition(position);

    this->setFillColor(sf::Color::Black);
    this->setOutlineColor(sf::Color::White);
    this->setOutlineThickness(4.0f);
}

void Asteroid::update(float delta)
{
    // std::cout << this->normals[0];
}

void Asteroid::calculateNormals()
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

