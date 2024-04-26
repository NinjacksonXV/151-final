#include <list>
#include <random>
#include "Asteroid.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

Asteroid::Asteroid(std::vector<sf::Vector2f> points, sf::Vector2f position)
{
    this->setPointCount(points.size());
    for (size_t i = 0; i < points.size(); i++)
    {
        setPoint(i, points[i]);
    }
    this->Object2D::setPosition(position);
    this->setColorPalette(Game::getColorPalette());
    this->setOutlineThickness(-4.0f);
}

Asteroid::Asteroid(unsigned int size)
{
    this->size = size;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> pos(windowAccessor->getView().getSize().x / -2.f, windowAccessor->getView().getSize().x / 2.f);
    std::uniform_real_distribution<float> speed(3.f, 35.f);
    std::uniform_int_distribution<> side(1, 4);

    asteroidAccessor->push_back(this);
    circumCirclePolygon();
    std::cout << "Got here";
    switch (side(gen))
    {
    case 1:
        Object2D::setPosition(windowAccessor->getView().getSize().x / 2.f + this->getLocalBounds().height / 2.f, pos(gen));
        break;
    case 2:
        Object2D::setPosition(windowAccessor->getView().getSize().x / -2.f - this->getLocalBounds().height / 2.f, pos(gen));
    case 3:
        Object2D::setPosition(pos(gen), windowAccessor->getView().getSize().x / 2.f + this->getLocalBounds().width / 2.f);
        break;
    case 4:
        Object2D::setPosition(pos(gen), windowAccessor->getView().getSize().x / -2.f - this->getLocalBounds().width / 2.f);
        break;
    }
    std::cout << "Got here2";

    this->velocity = AsteroidMath::Vector2::UP;
    velocity.rotate(pos(gen));
    velocity *= speed(gen);
    // calculateCentroid();
    // this->Object2D::setOrigin(this->calculateCentroid());
    this->setColorPalette(Game::getColorPalette());
    this->setOutlineThickness(-4.0f);
    std::cout << "Got here3";

}

Asteroid::Asteroid(unsigned int size, sf::Vector2f position)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> angles(0, M_PI * 2.f);

    this->size = size;
    circumCirclePolygon();
    this->Object2D::setPosition(position);
    // this->Object2D::setOrigin(this->calculateCentroid());
    this->setColorPalette(Game::getColorPalette());
    this->setOutlineThickness(-4.0f);
    asteroidAccessor->push_back(this);
    this->velocity = AsteroidMath::Vector2(angles(gen), angles(gen)) * angles(gen);
}

void Asteroid::setColorPalette(const ColorPalette &colorPalette)
{
    this->setFillColor(colorPalette.primary);
    this->setOutlineColor(colorPalette.secondary);
}

void Asteroid::update(float delta)
{
    Object2D::move(velocity * delta * 10.f);
    if (Object2D::getPosition().x > windowAccessor->getView().getSize().x / 2.f + getGlobalBounds().width / 2.f || Object2D::getPosition().x < windowAccessor->getView().getSize().x / -2.0f - getGlobalBounds().width / 2.f)
    {
        Object2D::setPosition(-1 * sign(this->Object2D::getPosition().x) * (windowAccessor->getView().getSize().x / 2.f + getGlobalBounds().width / 2.f), Object2D::getPosition().y);
    }
    if (Object2D::getPosition().y > windowAccessor->getView().getSize().y / 2.0f + getGlobalBounds().height / 2.f || Object2D::getPosition().y < windowAccessor->getView().getSize().y / -2.0f - getGlobalBounds().height / 2.f)
    {
        Object2D::setPosition(Object2D::getPosition().x, -1 * sign(this->Object2D::getPosition().y) * (windowAccessor->getView().getSize().y / 2.f + getGlobalBounds().height / 2.f));
    }
}

/**
 * @brief Called when a bullet hits. Provides the position of the bullet during impact and the indices of the polygons where the collision occured.
 *
 * @param position
 * @param point1
 * @param point2
 */
void Asteroid::impact(sf::Vector2f position, size_t point1, size_t point2)
{
    queueDelete = true;
}
void Asteroid::impact()
{
    if (this->size > 1)
    {
        new Asteroid(size - 1, this->Object2D::getPosition());
        new Asteroid(size - 1, this->Object2D::getPosition());
    }
    queueDelete = true;
}

// void Asteroid::calculateNormals()
// {
//     if (this->normals.capacity() != this->getPointCount())
//     {
//         this->normals.resize(this->getPointCount());
//     }
//     for (size_t i = 0; i < this->getPointCount(); i++)
//     {
//         sf::Vector2f p1 = this->getPoint(i); // I need a toGlobal() function for this and the one following.
//         sf::Vector2f p2 = this->getPoint(i + 1 == this->getPointCount() ? 0 : i + 1);

//         sf::Vector2f edge = p1 - p2;
//         AsteroidMath::Vector2 normal = {edge.y * -1, edge.x};
//         normal.normalize();
//         this->normals[i] = normal;
//     }
// }

/**
 * @brief Calculates the centroid of the polygon. Currently not functional...
 *
 * @return sf::Vector2f central point
 */
sf::Vector2f Asteroid::calculateCentroid()
{
    sf::Vector2f centroid;
    float signedArea;
    float x0 = 0.f,
          y0 = 0.f,
          x1 = 0.f,
          y1 = 0.f,
          a = 0.f;
    size_t i = 0;
    for (; i < getPointCount(); ++i)
    {
        x0 = getPoint(i).x;
        y0 = getPoint(i).y;
        x1 = getPoint(i + 1).x;
        y1 = getPoint(i + 1).y;
        a = x0 * y1 - x1 * y0;
        signedArea == a;
        centroid.x += (x0 + x1) * a;
        centroid.y += (y0 + y1) * a;
    }
    x0 = getPoint(i).x;
    y0 = getPoint(i).y;
    x1 = getPoint(0).x;
    y1 = getPoint(0).y;
    a = x0 * y1 - x1 * y0;
    signedArea += a;
    centroid.x += (x0 + x1) * a;
    centroid.y += (y0 + y1) * a;

    signedArea *= 0.5;
    centroid.x /= (6.0 * signedArea);
    centroid.y /= (6.0 * signedArea);
    return centroid;
}

/**
 * @brief Generates a circle-based polygon.
 *
 * Source: https://observablehq.com/@magrawala/random-convex-polygon
 *
 */
void Asteroid::circumCirclePolygon()
{
    float tooCloseThresholdRad = 10.f * 3.14159625 / 180.f;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> pointCount(4 + size, 5 * size);
    std::uniform_real_distribution<float> angles(0.0f, 1.0f);

    float radius = size * 40;

    size_t n = pointCount(gen);
    this->setPointCount(n);

    std::vector<float> vertAngles;
    for (size_t i = 0; i < n; i++)
    {
        float angle = angles(gen) * M_PI * 2.f;
        bool tooClose = false;
        for (float prevAngle : vertAngles)
        {
            float minAng = std::min(angle, prevAngle);
            float maxAng = std::max(angle, prevAngle);

            float diff = maxAng - minAng;
            if (diff < tooCloseThresholdRad || 2 * M_PI - diff < tooClose)
            {
                tooClose = true;
                break;
            }
        }
        if (tooClose == false)
            vertAngles.push_back(angle);
        else
            i--;
    }
    std::sort(vertAngles.begin(), vertAngles.end()); // Check back to see if this needs this sorting algorithm: [](float a, float b){ return a - b;}

    for (size_t i = 0; i < n; i++)
    {
        this->setPoint(i, {radius * cos(vertAngles[i]), radius * sin(vertAngles[i])});
    }
}