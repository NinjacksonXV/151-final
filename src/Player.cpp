#include "Player.hpp"
#include <SFML/Graphics.hpp>

int turnSpeed = 3;
int maxSpeed = 6;

void Player::update(float delta)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        //velocity += transform * AsteroidMath::Vector2::UP * delta; //TO-DO: Fix this so it works with sf::Transform properly. 
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        rotate(turnSpeed * delta);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        rotate(turnSpeed * delta * -1);
    }

    velocity.limitLength(maxSpeed);
    rotate(1 * delta);
}




