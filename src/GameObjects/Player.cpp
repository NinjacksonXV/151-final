#include "Player.hpp"
#include <math.h>

// Script variables are here for ease of use.

float minAccelerationVelocity = 1.5f;

float acceleration = 1000.f;
float deceleration = 1.0f;
float maxSpeed = 570.f;

float turnSpeed = 4.5f;
float rotationDelta;
float knockback = 1300.f;

unsigned int impacts = 2;

float rotationDeltaSpeedBoost = 1.4f;

float turnAroundSpeedBoostThreshold = -.8f;
float turnAroundSpeedBoost = 2.f;
float accelerationVisualCooldownLimit = .07f;
float accelerationVisualCooldown = 0.f;

float collisionGracePeriod;

bool spacePressed = false;

AsteroidMath::Vector2 direction;

int deathSpinDirection = 1;
float postDeathDelay;

float initializationTimer;

void Player::init()
{
    this->setPointCount(4);
    // When detecting collision, you need to transform these points by the player transform. Put this logic in GameplayShape
    setPoint(0, {-30, 10});
    setPoint(1, {0, -40});
    setPoint(2, {30, 10});
    setPoint(3, {0, 0});
    Object2D::setOrigin({0, -5});
    Object2D::setPosition({0, 0});
    setFillColor(Game::getColorPalette().primary);
    setOutlineColor(Game::getColorPalette().secondary);
    setOutlineThickness(4.0f);

    state = INITIALIZING;
    initializationTimer = 1.5f;

    direction = AsteroidMath::Vector2::UP;
}

void Player::setColorPalette(const ColorPalette &colorPalette)
{
    this->setFillColor(colorPalette.primary);
    this->setOutlineColor(colorPalette.secondary);
}

void Player::collided(sf::Vector2f impactVector, float magnitude)
{
    if (deathState == true || collisionGracePeriod > 0.f)
        return;
    Object2D::move(impactVector * magnitude);
    impacts--;
    collisionGracePeriod = .2f;
    this->velocity += asAMVector2(impactVector) * knockback;
    if (impacts == 0)
    {
        deathState = true;
        deathSpinDirection = sign(impactVector.x);
        velocity = velocity.limitLength(maxSpeed);
    }
    // std::cout << "Velocity: " << velocity << '\n';
}

/**
 * @brief Plays animation for dying, returns true when finished
 *
 * @param delta Delta time
 * @return true
 * @return false
 */
void Player::dieAnimation(float delta)
{
    if (rotationDelta == 0)
        rotationDelta = deathSpinDirection * turnSpeed;
    if (!((Object2D::getPosition().y > windowAccessor->getView().getSize().y / 2.0f + getGlobalBounds().height / 2.f || Object2D::getPosition().y < windowAccessor->getView().getSize().y / -2.0f - getGlobalBounds().height / 2.f) || (Object2D::getPosition().x > windowAccessor->getView().getSize().x / 2.f + getGlobalBounds().width / 2.f || Object2D::getPosition().x < windowAccessor->getView().getSize().x / -2.0f - getGlobalBounds().width / 2.f)))
    {
        Object2D::move(velocity * delta);
        Object2D::rotate(toDegrees(delta * rotationDelta * 2.f));
        postDeathDelay = 1.f;
    }
    else if (postDeathDelay > 0.f)
    {
        postDeathDelay -= delta;
    }
    else
        state = DEAD;
}

void Player::update(float delta)
{
    state = PLAYING; // TEMPORARY
    if (state == INITIALIZING && initializationTimer > 0.f)
    {
        initializationTimer -= delta;
    }
    else
        state = PLAYING;

    accelerationVisualCooldown -= delta;

    if (deathState == true)
    {
        if (accelerationVisualCooldown <= 0)
        {
            AsteroidMath::Vector2 tempRotation(cos(Object2D::getRotation() * M_PI / 180), sin(Object2D::getRotation() * M_PI / 180));
            sf::Vector2f temp((tempRotation * 15).getX(), (tempRotation * 15).getY());
            new AccelerationLine(this->Object2D::getPosition() - temp, tempRotation);
            accelerationVisualCooldown = accelerationVisualCooldownLimit;
        }
        dieAnimation(delta);
        return;
    }
    rotationDelta = 0.f;
    collisionGracePeriod -= delta;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        rotationDelta += turnSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        rotationDelta -= turnSpeed;
    }
    Object2D::rotate(toDegrees(rotationDelta * delta));
    direction.rotate(rotationDelta * delta);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        velocity += direction * acceleration * (rotationDelta != 0.f ? rotationDeltaSpeedBoost : 1.f) * delta;
        if (accelerationVisualCooldown <= 0)
        {
            sf::Vector2f temp((direction * 15).getX(), (direction * 15).getY());
            new AccelerationLine(this->Object2D::getPosition() - temp, direction);
            accelerationVisualCooldown = accelerationVisualCooldownLimit;
        }
    }
    else
    {
        velocity -= velocity * deceleration * delta;
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
    velocity = velocity.limitLength(maxSpeed);
    Object2D::move(velocity * delta);

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