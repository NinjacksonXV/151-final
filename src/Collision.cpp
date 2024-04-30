#include "Collision.hpp"
#include "GameObjects/Indicator.hpp"

bool Collision::checkForCollision(Bullet *bullet, Asteroid *asteroid)
{
    int pos = 0, neg = 0;
    bool entryPtLock = false;
    // sf::Vector2f entryPt1, entryPt2;
    size_t entryPt1 = 0;
    size_t entryPt2 = 1;
    float distance1 = 999999;
    float distance2 = 999999;
    float tempDistance1, tempDistance2;

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

        float crossProduct = (x - x1) * (y2 - y1) - (y - y1) * (x2 - x1);
        tempDistance1 = sqrt(pow(x - x1, 2) + pow(y - y1, 2));
        tempDistance2 = sqrt(pow(x - x2, 2) + pow(y - y2, 2));
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

        if (tempDistance1 < distance1)
        {
            entryPt1 = i;
            distance1 = tempDistance1;
        }
        if (tempDistance2 < distance2 && i2 != 0)
        {
            entryPt2 = i2;
            distance2 = tempDistance2;
        }
    }
    if (isInside)
    {
        // std::cout << distance1 << " ";
        // std::cout << distance2 << "\n";
        // new Indicator(asteroid->getTransformedPoint(entryPt1));
        // new Indicator(asteroid->getTransformedPoint(entryPt2));
        // new Indicator(bullet->Object2D::getPosition());

        if (bullet->collidedThisFrame == false)
        {
            asteroid->impact(asAMVector2(bullet->getHeading().normalized()));
        }
        bullet->impact();
        // asteroid->impact(bullet->Object2D::getPosition(), entryPt1, entryPt2);
    }
    return isInside;
}

void Collision::checkForCollision(Player *player, Asteroid *asteroid)
{
    std::vector<sf::Vector2f> playerAxes = player->getAxes();
    std::vector<sf::Vector2f> asteroidAxes = asteroid->getAxes();

    float overlap = 9999999;
    sf::Vector2f smallest;
    float tempOverlap;

    bool isColliding = true;
    for (size_t i = 0; i < playerAxes.size(); i++)
    {
        sf::Vector2f axis = playerAxes[i];
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
            smallest = {axis.x * -1, axis.y * -1};
        }
    }

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