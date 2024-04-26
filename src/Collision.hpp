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
        min = axis.dotProduct(asAMVector2(shape.getPoint(0)));
        max = min;
        for (size_t i = 1; i < shape.getCollisionPointCount(); i++)
        {
            float p = axis.dotProduct(asAMVector2(shape.getPoint(i)));
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
    bool overlaps(Projection projection)
    {
        return std::max(0.f, std::min(this->max, projection.max) - std::max(this->min, projection.min));
    }
};