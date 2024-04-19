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
    std::cout << "Initialization occured.";
    this->setPointCount(4);
    setPoint(0, {30, -10});
    setPoint(1, {0, 0});
    setPoint(2, {-30, -10});
    setPoint(3, {0, 40});
    setFillColor(sf::Color::Black);
    setOutlineColor(sf::Color::White);
    setOutlineThickness(4.0f);

    direction = AsteroidMath::Vector2::UP;
    TempStars *stars = new TempStars();
    children.push_back(stars);
    for (Object2D *child : children)
        child->init();
}

void Player::update(float delta)
{
    // std::cout << this->getPosition().x << " " << this->getPosition().y << '\n';
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
        velocity += direction * delta * 10.0f;
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
    // Make this block a member function of GameplayShape
    if (Object2D::getPosition().x > windowAccessor->getView().getSize().x / 2.f + getGlobalBounds().width / 2.f || Object2D::getPosition().x < windowAccessor->getView().getSize().x / -2.0f - getGlobalBounds().width / 2.f)
    {
        Object2D::setPosition(-1 * sign(this->Object2D::getPosition().x) * (windowAccessor->getView().getSize().x / 2.f + getGlobalBounds().width / 2.f), Object2D::getPosition().y);
    }
    if (Object2D::getPosition().y > windowAccessor->getView().getSize().y / 2.0f + getGlobalBounds().height / 2.f || Object2D::getPosition().y < windowAccessor->getView().getSize().y / -2.0f - getGlobalBounds().height / 2.f)
    {
        Object2D::setPosition(Object2D::getPosition().x, -1 * sign(this->Object2D::getPosition().y) * (windowAccessor->getView().getSize().y / 2.f + getGlobalBounds().height / 2.f));
    }

    children[0]->Object2D::setPosition(this->Object2D::getPosition());
    // std::cout << Object2D::getPosition() << '\n';
    // std::cout << getGlobalBounds().width << ", " << getGlobalBounds().height << '\n';
    std::cout << this->getLocalBounds();
    for (Object2D *child : children)
    {
        child->update(delta);
        break;
    }
}
