#include "Player.hpp"
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
float accelerationVisualCooldownLimit = .07f;
float accelerationVisualCooldown = 0.f;

bool spacePressed = false;

AsteroidMath::Vector2 direction;

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
}

void Player::setColorPalette(const ColorPalette &colorPalette)
{
    this->setFillColor(colorPalette.primary);
    this->setOutlineColor(colorPalette.secondary);
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
        velocity += direction * delta * acceleration;
        if (accelerationVisualCooldown <= 0)
        {
            sf::Vector2f temp((direction * 15).getX(), (direction * 15).getY());
            new AccelerationLine(this->Object2D::getPosition() - temp, direction);
            accelerationVisualCooldown = accelerationVisualCooldownLimit;
        }
    }
    else
    {
        velocity -= velocity * delta * deceleration;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if (spacePressed == false)
        {
            new Bullet(direction, Object2D::getPosition());
            spacePressed = true;
        }
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        spacePressed = false;
    }
    accelerationVisualCooldown -= delta;
    velocity = velocity.limitLength(maxSpeed);

    Object2D::move(velocity);

    // Screen wrapping
    if (Object2D::getPosition().x > windowAccessor->getView().getSize().x / 2.f + getGlobalBounds().width / 2.f || Object2D::getPosition().x < windowAccessor->getView().getSize().x / -2.0f - getGlobalBounds().width / 2.f)
    {
        Object2D::setPosition(-1 * sign(this->Object2D::getPosition().x) * (windowAccessor->getView().getSize().x / 2.f + getGlobalBounds().width / 2.f), Object2D::getPosition().y);
    }
    if (Object2D::getPosition().y > windowAccessor->getView().getSize().y / 2.0f + getGlobalBounds().height / 2.f || Object2D::getPosition().y < windowAccessor->getView().getSize().y / -2.0f - getGlobalBounds().height / 2.f)
    {
        Object2D::setPosition(Object2D::getPosition().x, -1 * sign(this->Object2D::getPosition().y) * (windowAccessor->getView().getSize().y / 2.f + getGlobalBounds().height / 2.f));
    }
}
