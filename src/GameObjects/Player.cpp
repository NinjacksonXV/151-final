#include "Player.hpp"
#include "../Utilities.hpp"
#include <math.h>

#define $ 

// Script variables are here for ease of use.
float acceleration = 3.f;
float turnSpeed = 3.f;
float maxSpeed = 4.f;

float turnAroundSpeedBoostThreshold = -.7f;
float turnAroundSpeedBoost = 2.f;

AsteroidMath::Vector2 direction;
AsteroidMath::Vector2 velocity;

sf::Vector2f distanceToScreenEdge;

void Player::init()
{
    this->setPointCount(4);
    setPoint(0, {30, 10});
    setPoint(1, {0, 0});
    setPoint(2, {-30, 10});
    setPoint(3, {0, -40});
    Object2D::setOrigin({0, -5});
    setFillColor(Game::getColorPalette().primary);
    setOutlineColor(Game::getColorPalette().secondary);
    setOutlineThickness(4.0f);

    direction = AsteroidMath::Vector2::UP;
    TempStars *stars = new TempStars();
    this->stars = stars;
    children.push_back(stars);
    for (Object2D *child : children)
        child->init();
}

void Player::update(float delta)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        Object2D::rotate(toDegrees(turnSpeed * delta));
        direction.rotate(turnSpeed * delta);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        Object2D::rotate(toDegrees(turnSpeed * delta * -1));
        direction.rotate(turnSpeed * delta * -1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        velocity += direction 
        * delta 
        * acceleration
        * (velocity.normalized().dotProduct(direction) < turnAroundSpeedBoostThreshold ? turnAroundSpeedBoost : 1.f);
        // std::cout << velocity.normalized().dotProduct(direction) << '\n';
    }
    else
    {
        velocity -= velocity * delta;
    }
    distanceToScreenEdge =
        {
            this->Object2D::getPosition().x - windowAccessor->getView().getSize().x / 2.f - getGlobalBounds().width / 2.f,
            this->Object2D::getPosition().y - windowAccessor->getView().getSize().y / 2.f - getGlobalBounds().height / 2.f};

    velocity = velocity.limitLength(maxSpeed);

    Object2D::move(velocity);
    stars->updatePosition(velocity);

    // Make this block a member function of GameplayShape
    if (Object2D::getPosition().x > windowAccessor->getView().getSize().x / 2.f + getGlobalBounds().width / 2.f || Object2D::getPosition().x < windowAccessor->getView().getSize().x / -2.0f - getGlobalBounds().width / 2.f)
    {
        Object2D::setPosition(-1 * sign(this->Object2D::getPosition().x) * (windowAccessor->getView().getSize().x / 2.f + getGlobalBounds().width / 2.f), Object2D::getPosition().y);
    }
    if (Object2D::getPosition().y > windowAccessor->getView().getSize().y / 2.0f + getGlobalBounds().height / 2.f || Object2D::getPosition().y < windowAccessor->getView().getSize().y / -2.0f - getGlobalBounds().height / 2.f)
    {
        Object2D::setPosition(Object2D::getPosition().x, -1 * sign(this->Object2D::getPosition().y) * (windowAccessor->getView().getSize().y / 2.f + getGlobalBounds().height / 2.f));
    }

    for (Object2D *child : children)
    {
        child->update(delta);
        break;
    }
}
