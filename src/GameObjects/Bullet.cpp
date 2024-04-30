#include "Bullet.hpp"
#include "../Utilities.hpp"
#include "../Game.hpp"

float speed = 1000.f;

Bullet::Bullet(sf::Vector2f rotation, sf::Vector2f playerPosition)
{
    offscreenCount = 0;
    this->setPointCount(4);
    this->setPoint(0, {-2.f, 0.f});
    this->setPoint(1, {2.f, 0.f});
    this->setPoint(2, {2.f, -5.f});
    this->setPoint(3, {-2.f, -5.f});

    this->Object2D::setPosition(playerPosition + (rotation * 25.f));
    this->setOutlineColor(Game::getColorPalette().secondary);
    this->setOutlineThickness(-4);

    this->Object2D::setRotation(toDegrees(atan(rotation.y / rotation.x)) - 90);
    this->travelRotation = rotation;
    collidedThisFrame = false;
    bulletAccessor->push_back(this);
}

void Bullet::update(float delta)
{
    this->Object2D::move(travelRotation * speed * delta);
    // std::cout << this->Object2D::getPosition() << '\n';
    if (Object2D::getPosition().x > windowAccessor->getView().getSize().x / 2.f + getGlobalBounds().width / 2.f || Object2D::getPosition().x < windowAccessor->getView().getSize().x / -2.0f - getGlobalBounds().width / 2.f)
    {
        offscreenCount++;
        Object2D::setPosition(-1 * sign(this->Object2D::getPosition().x) * (windowAccessor->getView().getSize().x / 2.f + getGlobalBounds().width / 2.f), Object2D::getPosition().y);
    }
    if (Object2D::getPosition().y > windowAccessor->getView().getSize().y / 2.0f + getGlobalBounds().height / 2.f || Object2D::getPosition().y < windowAccessor->getView().getSize().y / -2.0f - getGlobalBounds().height / 2.f)
    {
        offscreenCount++;
        Object2D::setPosition(Object2D::getPosition().x, -1 * sign(this->Object2D::getPosition().y) * (windowAccessor->getView().getSize().y / 2.f + getGlobalBounds().height / 2.f));
    }
    if (offscreenCount == 2) queueDelete = true;
}

void Bullet::impact()
{
    collidedThisFrame = true;
    queueDelete = true;
}
