#include "Collision.hpp"
#include "GameObjects/Indicator.hpp"

bool Collision::checkForCollision(Bullet *bullet, Asteroid *asteroid)
{
    int pos = 0, neg = 0;
    bool entryPtLock = false;
    size_t entryPt1;
    size_t entryPt2;
    bool isInside = true;
    for (size_t i = 0; i < asteroid->getPointCount(); i++)
    {
        if (asteroid->getPoint(i) == bullet->Object2D::getPosition())
        {
            isInside = true;
        }
        float x1 = asteroid->Object2D::getTransform().transformPoint(asteroid->getPoint(i)).x;
        float y1 = asteroid->Object2D::getTransform().transformPoint(asteroid->getPoint(i)).y;

        size_t i2 = (i + 1) % asteroid->getPointCount();

        float x2 = asteroid->Object2D::getTransform().transformPoint(asteroid->getPoint(i2)).x;
        float y2 = asteroid->Object2D::getTransform().transformPoint(asteroid->getPoint(i2)).y;

        float x = bullet->Object2D::getPosition().x;
        float y = bullet->Object2D::getPosition().y;

        float crossProduct = (x - x1) * (y2 - y1) - (y - y1) * (x2 - x1);
        if (crossProduct > 0.f)
            pos++;
        if (crossProduct < 0.f)
            neg++;
        if (pos > 0 && neg > 0)
            isInside = false;
        else
        {
            if (entryPtLock == false)
            {
                entryPt1 = i;
                entryPt2 = i2;
                entryPtLock = true;
            }
        }
    }
    if (isInside)
    {
        // new Indicator(asteroid->getPoint(entryPt1));
        // new Indicator(asteroid->getPoint(entryPt2));
        // new Indicator(bullet->Object2D::getPosition());

        bullet->impact();
        // asteroid->impact(bullet->Object2D::getPosition(), entryPt1, entryPt2);
        asteroid->impact();
    }
    return isInside;
}

void Collision::checkForCollision(Player *player, Asteroid *asteroid)
{
    std::vector<sf::Vector2f> playerAxes = player->getAxes();
    std::vector<sf::Vector2f> asteroidAxes = asteroid->getAxes();

    bool isColliding = true;
    for (size_t i = 0; i < playerAxes.size(); i++)
    {
        sf::Vector2f axis = playerAxes[i];
        Projection p1(*player, asAMVector2(axis));
        Projection p2(*asteroid, asAMVector2(axis));

        std::cout << p1.min << ' ' << p1.max << '\n';
        std::cout << p2.min << ' ' << p2.max << '\n';

        if (p1.overlaps(p2) == false)
        {
            // std::cout << "FALSIFIED\n";
            isColliding = false;
            return;
        }
    }
    if (!isColliding)
        return;
    for (size_t i = 0; i < asteroidAxes.size(); i++)
    {
        sf::Vector2f axis = asteroidAxes[i];
        Projection p1(*player, asAMVector2(axis));
        Projection p2(*asteroid, asAMVector2(axis));

        if (p1.overlaps(p2) == false)
        {
            // std::cout << "FALSIFIED";
            isColliding = false;
            return;
        }
    }
    if (isColliding) std::cout << "IS COLLIDING \n";

}

// void Collision::checkForCollision(Bullet *bullet, Asteroid *asteroid)
// {
//     AsteroidMath::Vector2 bulletVel = {bullet->getVelocity().x, bullet->getVelocity().y};

//     float x = bullet->Object2D::getPosition().x;
//     float y = bullet->Object2D::getPosition().y;

//     size_t entryPt1;
//     size_t entryPt2;
//     sf::Vector2f entryPosition;

//     size_t exitPt1;
//     size_t exitPt2;
//     sf::Vector2f exitPosition;

//     bool entryPtLock = false;

//     bool isInside = false;

//     sf::Vector2f p1 = asteroid->getPoint(0), p2;
//     for (size_t i = 1; i < asteroid->getPointCount(); i++)
//     {
//         p2 = asteroid->getPoint(i % asteroid->getPointCount());
//         if (y > std::min(p1.y, p2.y))
//         {
//             if (y <= std::max(p1.y, p2.y))
//             {
//                 if (x <= std::max(p1.x, p2.x))
//                 {
//                     float xIntersection = (y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y) + p1.x;
//                     if (p1.x == p2.x || x <= xIntersection)
//                     {
//                         isInside = !isInside;
//                         if (entryPtLock == false)
//                         {
//                             entryPosition = bullet->Object2D::getPosition();
//                             entryPt1 = i - 1;
//                             entryPt2 = i % asteroid->getPointCount();
//                             entryPtLock = true;
//                         }
//                     }
//                 }
//             }
//             p1 = p2;
//         }
//     }
//     if (isInside)
//     {
//         bullet->impact();
//         asteroid->impact(bullet->Object2D::getPosition(), entryPt1, entryPt2);
//     }
// }