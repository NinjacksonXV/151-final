#pragma once

#include "../Utilities.hpp"
#include "GameplayShape.hpp"

extern sf::RenderTarget const *windowAccessor;

struct SizeVals
{
    SizeVals(unsigned int size, float minSpeed, float maxSpeed, float maxRotationSpeed, unsigned int minPointCount, unsigned int maxPointCount, unsigned int minRadius, unsigned int maxRadius)
        : size(size), minSpeed(minSpeed), maxSpeed(maxSpeed), maxRotationSpeed(maxRotationSpeed), minPointCount(minPointCount), maxPointCount(maxPointCount), minRadius(minRadius), maxRadius(maxRadius){};
    unsigned int size;
    float maxSpeed;
    float minSpeed;
    float maxRotationSpeed;
    unsigned int minPointCount;
    unsigned int maxPointCount;
    unsigned int minRadius;
    unsigned int maxRadius;

    static SizeVals& getSize(unsigned int size);
};

class Asteroid : public GameplayShape
{
public:
    Asteroid(std::vector<sf::Vector2f> points, sf::Vector2f position);
    Asteroid(unsigned int size);
    Asteroid(unsigned int size, sf::Vector2f position);
    void setColorPalette(const ColorPalette &colorPalette);
    void update(float delta) override;

    void impact(sf::Vector2f position, size_t point1, size_t point2);
    void impact();
    bool queueDelete = false;

private:
    SizeVals size;
    // void split();
    mutable sf::FloatRect rect;
    sf::Vector2f calculateCentroid();

    // void generatePolygon();
    // void generateValtrPolygon();
    void circumCirclePolygon();
};
extern std::list<Asteroid *> *asteroidAccessor;