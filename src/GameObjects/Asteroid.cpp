#include <list>
#include <random>
#include "Asteroid.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

unsigned int Asteroid::points;

SizeVals &SizeVals::getSize(unsigned int size)
{
    static SizeVals sizes[] =
        {
            SizeVals(1, 20, 7.f, 35.f, .7f, 5, 8, 30, 40),    // Size 1
            SizeVals(2, 15, 4.f, 20.f, .7f, 9, 12, 50, 70),   // Size 2
            SizeVals(3, 10, 4.f, 15.f, .7f, 13, 15, 80, 110), // Size 3
            SizeVals(4, 5, 4.f, 8.f, 3.f, 16, 22, 130, 160),  // Size 4
        };

    if (size > sizeof(sizes) / sizeof(SizeVals))
    {
        throw std::runtime_error("Wrong size");
    }
    return sizes[size - 1];
}

Asteroid::Asteroid(unsigned int size) : size(SizeVals::getSize(size)), hasNotBeenOnScreen(true)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> pos(
        (gameViewAccessor->getSize().x / -2.f) + 100.f,
        (gameViewAccessor->getSize().x / 2.f) - 100.f);
    std::uniform_real_distribution<float> speed(this->size.minSpeed, this->size.maxSpeed);
    std::uniform_real_distribution<float> rot(M_PI / -3.f, M_PI / 3.f);
    std::uniform_int_distribution<> side(1, 4);

    asteroidAccessor->push_back(this);
    circumCirclePolygon();
    switch (side(gen))
    {
    case 1:
        Object2D::setPosition((gameViewAccessor->getSize().x / 2.f) + this->getLocalBounds().width, pos(gen));
        this->velocity = AsteroidMath::Vector2::LEFT;
        break;
    case 2:
        Object2D::setPosition(gameViewAccessor->getSize().x / -2.f - this->getLocalBounds().width, pos(gen));
        this->velocity = AsteroidMath::Vector2::RIGHT;
        break;
    case 3:
        Object2D::setPosition(pos(gen), gameViewAccessor->getSize().x / 2.f + this->getLocalBounds().height);
        this->velocity = AsteroidMath::Vector2::UP;
        break;
    case 4:
        Object2D::setPosition(pos(gen), gameViewAccessor->getSize().x / -2.f - this->getLocalBounds().height);
        this->velocity = AsteroidMath::Vector2::DOWN;
        break;
    }

    velocity.rotate(rot(gen));
    velocity *= speed(gen);
    this->setColorPalette(Game::getColorPalette());
    this->setOutlineThickness(-4.0f);
}

Asteroid::Asteroid(unsigned int size, sf::Vector2f position, sf::Vector2f direction) : size(SizeVals::getSize(size))
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> speed(this->size.minSpeed, this->size.maxSpeed);

    float generatedSpeed = speed(gen);
    circumCirclePolygon();
    this->Object2D::setPosition(position);
    this->velocity = asAMVector2(direction) * generatedSpeed;
    this->setColorPalette(Game::getColorPalette());
    this->setOutlineThickness(-4.0f);
    asteroidAccessor->push_back(this);
}

void Asteroid::setColorPalette(const ColorPalette &colorPalette)
{
    this->setFillColor(colorPalette.primary);
    this->setOutlineColor(colorPalette.secondary);
}

bool Asteroid::checkIfHasNotBeenOnScreen()
{
    if (abs(this->Object2D::getPosition().x) > gameViewAccessor->getSize().x / 2.f && abs(this->Object2D::getPosition().y) > gameViewAccessor->getSize().y)
        hasNotBeenOnScreen = false;
    return hasNotBeenOnScreen;
}

void Asteroid::update(float delta)
{
    Object2D::move(velocity * delta * 10.f);

    if (checkIfHasNotBeenOnScreen())
        return;

    if (Object2D::getPosition().x > gameViewAccessor->getSize().x / 2.f + getGlobalBounds().width / 2.f || Object2D::getPosition().x < gameViewAccessor->getSize().x / -2.0f - getGlobalBounds().width / 2.f)
    {
        Object2D::setPosition(-1 * sign(this->Object2D::getPosition().x) * (gameViewAccessor->getSize().x / 2.f + getGlobalBounds().width / 2.f), Object2D::getPosition().y);
    }
    if (Object2D::getPosition().y > gameViewAccessor->getSize().y / 2.0f + getGlobalBounds().height / 2.f || Object2D::getPosition().y < gameViewAccessor->getSize().y / -2.0f - getGlobalBounds().height / 2.f)
    {
        Object2D::setPosition(Object2D::getPosition().x, -1 * sign(this->Object2D::getPosition().y) * (gameViewAccessor->getSize().y / 2.f + getGlobalBounds().height / 2.f));
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

void Asteroid::impact(AsteroidMath::Vector2 bulletDirection)
{
    if (this->size.size > 1)
    {
        AsteroidMath::Vector2 direction1 = {bulletDirection.getY() * -1, bulletDirection.getX()};
        AsteroidMath::Vector2 newPosition1 = direction1 * SizeVals::getSize(size.size - 1).maxRadius;

        AsteroidMath::Vector2 direction2 = direction1;
        direction2.rotate(M_PI);
        AsteroidMath::Vector2 newPosition2 = newPosition2 * SizeVals::getSize(size.size - 1).maxRadius;

        sf::Vector2f temp1 = this->Object2D::getTransform().transformPoint(newPosition1);
        sf::Vector2f temp2 = this->Object2D::getTransform().transformPoint(newPosition2);

        // Couldn't figure out how to offset the asteroids. Doesn't look bad, regardless.
        new Asteroid(size.size - 1, this->Object2D::getPosition(), direction1);
        new Asteroid(size.size - 1, this->Object2D::getPosition(), direction2);
    }
    Asteroid::points += this->size.pointValue;
    queueDelete = true;
}

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
        signedArea = a;
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

    std::uniform_int_distribution<int> pointCount(size.minPointCount, size.maxPointCount);
    std::uniform_real_distribution<float> angles(0.0f, 1.0f);
    std::uniform_real_distribution<float> radii(size.minRadius, size.maxRadius);

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

    float radius = radii(gen);
    for (size_t i = 0; i < n; i++)
    {
        this->setPoint(i, {radius * cos(vertAngles[i]), radius * sin(vertAngles[i])});
    }
}