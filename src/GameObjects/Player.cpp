#include "Player.hpp"
#include "../Utilities.hpp"
#include <math.h>

// Script variables are here for ease of use.

float minAccelerationVelocity = 1.5f;

float acceleration = 8.f;
float deceleration = 1.0f;
float turnSpeed = 3.f;
float maxSpeed = 4.f;

float rotationDeltaSpeedBoost = 1.5f;

float turnAroundSpeedBoostThreshold = -.8f;
float turnAroundSpeedBoost = 2.f;

AsteroidMath::Vector2 direction;
AsteroidMath::Vector2 velocity;

sf::Vector2f distanceToScreenEdge;

void Player::init()
{
    this->setPointCount(4);
    // When detecting collision, you need to transform these points by the player transform. Put this logic in GameplayShape
    setPoint(0, {-30, 10});
    setPoint(1, {0, -40});
    setPoint(2, {30, 10});
    setPoint(3, {0, 0});
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

void Player::setColorPalette(const ColorPalette &colorPalette)
{
    this->setFillColor(colorPalette.primary);
    this->setOutlineColor(colorPalette.secondary);
    stars->setColorPalette(colorPalette);
}

void Player::update(float delta)
{
    float rotationDelta = 0.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        rotationDelta += turnSpeed * delta;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        rotationDelta -= turnSpeed * delta;
    }
    Object2D::rotate(toDegrees(rotationDelta));
    direction.rotate(rotationDelta);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        // if (velocity.getLength() < minAccelerationVelocity && velocity.normalized().dotProduct(direction) > 0) velocity = direction * minAccelerationVelocity;
        velocity += direction * delta * acceleration;
        // * (velocity.normalized().dotProduct(direction) < turnAroundSpeedBoostThreshold
        //  ? turnAroundSpeedBoost
        //  : 1.f);

        // std::cout << velocity.normalized().dotProduct(direction) << '\n';
        // if (velocity.normalized().dotProduct(direction) < 0.f)
        // {
        //     std::cout << velocity.dotProduct(direction)
        //     << " * "
        //     << turnAroundSpeedBoost
        //     << " = "
        //     << velocity.normalized().dotProduct(direction) * turnAroundSpeedBoost << '\n';
        // }
        
        // * (rotationDelta ? rotationDeltaSpeedBoost : 1.f);
    }
    else
    {
        velocity -= velocity * delta * deceleration;
    }

    distanceToScreenEdge =
        {
            this->Object2D::getPosition().x - windowAccessor->getView().getSize().x / 2.f - getGlobalBounds().width / 2.f,
            this->Object2D::getPosition().y - windowAccessor->getView().getSize().y / 2.f - getGlobalBounds().height / 2.f};

    velocity = velocity.limitLength(maxSpeed);

    Object2D::move(velocity);
    stars->updatePosition(velocity);

    // Screen wrapping
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
