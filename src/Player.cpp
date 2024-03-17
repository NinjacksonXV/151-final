#include "Player.hpp"
#include <SFML/Graphics.hpp>
// TO-DO: Replace with AsteroidMath::Transform
sf::Transform transform = sf::Transform::Identity;
sf::Vector2f velocity;

void Player::update(float delta)
{
    rotate(1 * delta);
}




