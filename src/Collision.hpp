#pragma once
#include "GameObjects/Player.hpp"
#include "GameObjects/Bullet.hpp"
#include "GameObjects/Asteroid.hpp"

#include <vector>

class Collision
{
public:
    static bool checkForCollision(Bullet *bullet, Asteroid *asteroid);
    static void checkForCollision(Player *player, Asteroid *asteroid);
};

struct Projection
{
    float min;
    float max;
    Projection(GameplayShape &shape, AsteroidMath::Vector2 axis)
    {
        // std::cout << "\n\n";
        min = axis.dotProduct(asAMVector2(shape.getTransformedPoint(0)));
        // std::cout << axis << " dot product with " << shape.getTransformedPoint(0) << " = " << min;
        max = min;
        // std::cout << "Starter min: " << min << '\n';
        // std::cout << "Starter max: " << max << '\n';

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
        // std::cout << "End min: " << min << '\n';
        // std::cout << "End max: " << max << '\n';
    }
    float overlaps(Projection projection)
    {
        return std::max(0.f, std::min(this->max, projection.max) - std::max(this->min, projection.min));
    }
};