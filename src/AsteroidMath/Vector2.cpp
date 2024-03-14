#include "Vector2.hpp"

const AsteroidMath::Vector2 AsteroidMath::Vector2::UP = AsteroidMath::Vector2(0, 1);
const AsteroidMath::Vector2 AsteroidMath::Vector2::DOWN = AsteroidMath::Vector2(0, -1);
const AsteroidMath::Vector2 AsteroidMath::Vector2::LEFT = AsteroidMath::Vector2(-1, 0);
const AsteroidMath::Vector2 AsteroidMath::Vector2::RIGHT = AsteroidMath::Vector2(1, 0);
const AsteroidMath::Vector2 AsteroidMath::Vector2::ZERO = AsteroidMath::Vector2(0, 0);

AsteroidMath::Vector2::Vector2(float x, float y)
{
    this->x = x;
    this->y = y;
    this->updateLength();
}

float AsteroidMath::Vector2::getX() const
{
    return this->x;
}

float AsteroidMath::Vector2::getY() const
{
    return this->y;
}

float AsteroidMath::Vector2::getLength() const
{
    return this->length;
}

void AsteroidMath::Vector2::setX(float x)
{
    this->x = x;
    updateLength();
}

void AsteroidMath::Vector2::setY(float y)
{
    this->y = y;
    updateLength();
}

void AsteroidMath::Vector2::setLength(float length)
{
    float ratio = this->length / length;
    this->x *= ratio;
    this->y *= ratio;
    this->length = length;
}

void AsteroidMath::Vector2::rotate(float radians)
{
    // Vector rotation formula
    float newX = std::cos(radians * this->x) - std::sin(radians * this->y);
    float newY = std::sin(radians * this->x) + std::cos(radians * this->y);
    this->x = newX;
    this->y = newY;
}

void AsteroidMath::Vector2::limitLength(float limit)
{
    if (this->length < length)
        return;
    setLength(limit);
}

void AsteroidMath::Vector2::normalize()
{
    this->setLength(1);
}

void AsteroidMath::Vector2::updateLength()
{
    length = sqrt(pow(this->x, 2) + pow(this->y, 2));
}
