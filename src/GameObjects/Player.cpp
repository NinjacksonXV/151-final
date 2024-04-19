#include "Player.hpp"
#include "../Utilities.hpp"
#include <math.h>

// Script variables are here for ease of use.
int turnSpeed = 3;
int maxSpeed = 5.0f;
AsteroidMath::Vector2 direction;
AsteroidMath::Vector2 velocity;
sf::Vector2f distanceToScreenEdge;

void Player::init()
{
    direction = AsteroidMath::Vector2::UP;
    TempStars *stars = new TempStars();
    PlayerShape *playerShape = new PlayerShape();
    children.push_back(stars);
    children.push_back(playerShape);
    this->shapePtr = playerShape;
    for (Object2D *child : children)
        child->init();
}

void Player::update(float delta)
{
    // std::cout << this->getPosition().x << " " << this->getPosition().y << '\n';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        rotate(toDegrees(turnSpeed * delta));
        direction.rotate(turnSpeed * delta);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        rotate(toDegrees(turnSpeed * delta * -1));
        direction.rotate(turnSpeed * delta * -1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        velocity += direction * delta * 10.0f;
    }
    else
    {
        velocity -= velocity * delta;
    }

    distanceToScreenEdge =
    {
        this->getPosition().x - windowAccessor->getView().getSize().x / 2.f - shapePtr->getGlobalBounds().width / 2.f,
        this->getPosition().y - windowAccessor->getView().getSize().y / 2.f - shapePtr->getGlobalBounds().height / 2.f
    };

    velocity = velocity.limitLength(maxSpeed);

    move(velocity);
    // Make this block a member function of GameplayShape
    if (getPosition().x > windowAccessor->getView().getSize().x / 2.f + shapePtr->getGlobalBounds().width / 2.f
     || getPosition().x < windowAccessor->getView().getSize().x / -2.0f - shapePtr->getGlobalBounds().width / 2.f)
    {
        setPosition(-1 * sign(this->getPosition().x) * (windowAccessor->getView().getSize().x / 2.f + shapePtr->getGlobalBounds().width / 2.f), getPosition().y);
    }
    if (getPosition().y > windowAccessor->getView().getSize().y / 2.0f + shapePtr->getGlobalBounds().height / 2.f
     || getPosition().y < windowAccessor->getView().getSize().y / -2.0f - shapePtr->getGlobalBounds().height / 2.f)
    {
        setPosition(getPosition().x, -1 * sign(this->getPosition().y) * (windowAccessor->getView().getSize().y / 2.f + shapePtr->getGlobalBounds().height / 2.f));
    }

    children[0]->setPosition(this->getPosition());
    std::cout << getPosition() << '\n';
    // std::cout << shapePtr->getGlobalBounds().width << ", " << shapePtr->getGlobalBounds().height << '\n';
    // std::cout << this->shapePtr->getLocalBounds();
    for (Object2D *child : children)
    {
        child->update(delta);
        break;
    }
}

