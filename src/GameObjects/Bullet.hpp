#pragma once
#include <list>
#include "Object2D.hpp"
#include "../Utilities.hpp"

extern sf::RenderTarget const *windowAccessor;

class Bullet : public Object2D, public sf::ConvexShape
{
public:
    Bullet(sf::Vector2f rotation, sf::Vector2f position);
    void init() override{};
    void update(float deltaTime) override;

    AsteroidMath::Vector2 getHeading() { return asAMVector2(travelRotation); }
    /**
     * @brief Runs logic when this bullet collides with an asteroid.
     *
     */
    void impact();
    bool queueDelete = false;
    bool collidedThisFrame = false; // Here so that we don't run into vector range exceptions in the update loop

private:
    sf::Vector2f travelRotation; // rotation of the object as a vector
    short int offscreenCount;    // How many times the bullet has screenwrapped

    // Look at Object2D::onDraw() for documentation.
    void onDraw(sf::RenderTarget &target, const sf::Transform &) const
    {
        target.draw(*this, this->Object2D::getTransform());
    };
};

extern std::list<Bullet *> *bulletAccessor;