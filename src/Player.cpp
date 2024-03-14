#include <SFML/Graphics.hpp>
#include "Player.hpp"


sf::Transform transform = sf::Transform::Identity;
sf::Vector2f velocity;

void update(float delta)
{

    transform.rotate(1 * delta);
}




