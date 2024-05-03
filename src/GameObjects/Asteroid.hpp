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
    /**
     * @brief Instantiate an asteroid that spawns off-screen and flys inwards
     *
     * @param size Size of the asteroid to spawn
     */
    Asteroid(unsigned int size);

    /**
     * @brief Construct a new Asteroid object
     *
     * @param size Size of the asteroid to spawn 
     * @param position Position of the new asteroid
     * @param direction Direction that the asteroid should fly in
     */
    Asteroid(unsigned int size, sf::Vector2f position, sf::Vector2f direction);
    void setColorPalette(const ColorPalette &colorPalette);
    void update(float delta) override;

    /**
     * @brief Runs when the asteroid
     *
     * @param bulletDirection
     */
    void impact(AsteroidMath::Vector2 bulletDirection);
    bool queueDelete = false;

    unsigned int getSize() { return size.size; }

    static unsigned int points;

private:
    SizeVals size;
    mutable sf::FloatRect rect;
    sf::Vector2f calculateCentroid(); // Unused

    /**
     * @brief Generates a circle-based polygon.
     *
     * Source: https://observablehq.com/@magrawala/random-convex-polygon
     *
     */
    void circumCirclePolygon();
    bool checkIfHasNotBeenOnScreen();
    bool hasNotBeenOnScreen;
};
extern std::list<Asteroid *> *asteroidAccessor;