#include "Collision.hpp"
#include "GameObjects/Indicator.hpp"

bool Collision::checkForCollision(Bullet *bullet, Asteroid *asteroid)
{
    int pos = 0, neg = 0;

    bool isInside = true;
    for (size_t i = 0; i < asteroid->getPointCount(); i++)
    {
        if (asteroid->getPoint(i) == bullet->Object2D::getPosition())
        {
            isInside = true;
        }
        float x1 = asteroid->getTransformedPoint(i).x;
        float y1 = asteroid->getTransformedPoint(i).y;

        size_t i2 = (i + 1) % asteroid->getCollisionPointCount();

        float x2 = asteroid->getTransformedPoint(i2).x;
        float y2 = asteroid->getTransformedPoint(i2).y;

        float x = bullet->Object2D::getPosition().x;
        float y = bullet->Object2D::getPosition().y;

        // Essentially make a raycast from the given point through the shape. 
        float crossProduct = (x - x1) * (y2 - y1) - (y - y1) * (x2 - x1);

        if (crossProduct > 0.f)
        {
            pos++;
        }
        if (crossProduct < 0.f)
        {
            neg++;
        }
        if (pos > 0 && neg > 0)
            isInside = false;
    }
    if (isInside)
    {
        if (bullet->collidedThisFrame == false)
        {
            asteroid->impact(asAMVector2(bullet->getHeading().normalized()));
        }
        bullet->impact();
    }
    return isInside;
}

void Collision::checkForCollision(Player *player, Asteroid *asteroid)
{
    std::vector<sf::Vector2f> playerAxes = player->getAxes();
    std::vector<sf::Vector2f> asteroidAxes = asteroid->getAxes();

    float overlap = 9999999; // Large value to find the minimum overlap for MTV
    sf::Vector2f smallest;   // Vector tied to the smallest overlap 
    float tempOverlap;

    bool isColliding = true;
    for (size_t i = 0; i < playerAxes.size(); i++)
    {
        sf::Vector2f axis = playerAxes[i];

        // Project the shapes onto the given axis
        Projection p1(*player, asAMVector2(axis));
        Projection p2(*asteroid, asAMVector2(axis));

        tempOverlap = p1.overlaps(p2);
        if (tempOverlap == 0.f)
        {
            // if the overlap fails, then we're not colliding 
            isColliding = false;
            return;
        }
        else if (tempOverlap < overlap)
        {
            // if the overlap is smaller than the current smallest one, it's the more accurate MTV 
            overlap = tempOverlap;
            smallest = {axis.x * -1, axis.y * -1};
        }
    }

    // Do it again for the asteroid axes. 
    for (size_t i = 0; i < asteroidAxes.size(); i++)
    {
        sf::Vector2f axis = asteroidAxes[i];
        Projection p1(*player, asAMVector2(axis));
        Projection p2(*asteroid, asAMVector2(axis));

        tempOverlap = p1.overlaps(p2);

        if (tempOverlap == 0.f)
        {
            isColliding = false;
            return;
        }
        else if (tempOverlap < overlap)
        {
            overlap = tempOverlap;
            smallest = axis;
        }
    }
    if (isColliding)
    {
        player->collided(smallest, overlap);
    }
}