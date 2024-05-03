#pragma once
#include "GameObjects/Player.hpp"
#include "GameObjects/Bullet.hpp"
#include "GameObjects/Asteroid.hpp"

#include <vector>

class Collision
{
public:
    /**
     * @brief Checks for collision between a bullet and an asteroid
     *
     * @param bullet
     * @param asteroid
     */
    static bool checkForCollision(Bullet *bullet, Asteroid *asteroid);

    /**
     * @brief Checks for collision between the player and an asteroid.
     *
     * @param player
     * @param asteroid
     */
    static void checkForCollision(Player *player, Asteroid *asteroid);
};

/**
 * @brief Projects a shape onto a given normalized axis.
 *
 */
struct Projection
{
    float min;
    float max;

    Projection(GameplayShape &shape, AsteroidMath::Vector2 axis)
    {
        min = axis.dotProduct(asAMVector2(shape.getTransformedPoint(0)));
        max = min;
        for (size_t i = 1; i < shape.getCollisionPointCount(); i++)
        {
            float p = axis.dotProduct(asAMVector2(shape.getTransformedPoint(i)));
            if (p < min)
            {
                min = p;
            }
            else if (p > max)
            {
                max = p;
            }
        }
    }

    // Checks if one projection overlaps another.
    float overlaps(Projection projection)
    {
        return std::max(0.f, std::min(this->max, projection.max) - std::max(this->min, projection.min));
    }
};