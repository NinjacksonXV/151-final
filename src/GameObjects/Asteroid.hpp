#pragma once
#include <SFML/Audio.hpp>

#include "../Utilities.hpp"
#include "GameplayShape.hpp"

extern sf::RenderTarget const *windowAccessor;
extern sf::View const *gameViewAccessor;

struct SizeVals
{
    SizeVals(unsigned int size, unsigned int pointValue, float minSpeed, float maxSpeed, float maxRotationSpeed, unsigned int minPointCount, unsigned int maxPointCount, unsigned int minRadius, unsigned int maxRadius)
        : size(size), pointValue(pointValue), minSpeed(minSpeed), maxSpeed(maxSpeed), maxRotationSpeed(maxRotationSpeed), minPointCount(minPointCount), maxPointCount(maxPointCount), minRadius(minRadius), maxRadius(maxRadius){};
    unsigned int size;
    unsigned int pointValue;
    float minSpeed;
    float maxSpeed;
    float maxRotationSpeed;
    unsigned int minPointCount;
    unsigned int maxPointCount;
    unsigned int minRadius;
    unsigned int maxRadius;

    static SizeVals &getSize(unsigned int size);
};

class Asteroid : public GameplayShape
{
public:
    Asteroid(unsigned int size);
    Asteroid(unsigned int size, sf::Vector2f position, sf::Vector2f direction);
    void setColorPalette(const ColorPalette &colorPalette);
    void update(float delta) override;

    void impact(sf::Vector2f position, size_t point1, size_t point2);
    void impact(AsteroidMath::Vector2 bulletDirection);
    bool queueDelete = false;

    unsigned int getSize() { return size.size; }

    static unsigned int points;

private:
    SizeVals size;
    // void split();
    mutable sf::FloatRect rect;
    sf::Vector2f calculateCentroid();

    // void generatePolygon();
    // void generateValtrPolygon();
    void circumCirclePolygon();
    bool checkIfHasNotBeenOnScreen();
    bool hasNotBeenOnScreen;
};
extern std::list<Asteroid *> *asteroidAccessor;