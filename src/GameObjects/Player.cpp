#include "Player.hpp"
#include "../Utilities.hpp"

// Script variables are here for ease of use.
int turnSpeed = 3;
int maxSpeed = 5.0f;
AsteroidMath::Vector2 direction;
AsteroidMath::Vector2 velocity;

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
    velocity = velocity.limitLength(maxSpeed);
    move(velocity);
    children[0]->setPosition(this->getPosition());
    for (Object2D *child : children)
    {
        child->update(delta);
        break;
    }
}