#pragma once
#include <vector>

enum class CollisionLayer
{
    c_Player,
    c_Asteroid,
    c_Bullet
};

class Collidable
{
    private:
    std::vector<CollisionLayer> collisionLayers;
    void initializeCollision()
    {
        // for (CollisionLayer collisionLayer : collisionLayers)
        // {
        //     Game::
        // }
    };
};