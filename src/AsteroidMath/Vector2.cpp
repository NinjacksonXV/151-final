#include "Vector2.hpp"

const AsteroidMath::Vector2 AsteroidMath::Vector2::UP = AsteroidMath::Vector2(0, -1);
const AsteroidMath::Vector2 AsteroidMath::Vector2::DOWN = AsteroidMath::Vector2(0, 1);
const AsteroidMath::Vector2 AsteroidMath::Vector2::LEFT = AsteroidMath::Vector2(-1, 0);
const AsteroidMath::Vector2 AsteroidMath::Vector2::RIGHT = AsteroidMath::Vector2(1, 0);
const AsteroidMath::Vector2 AsteroidMath::Vector2::ZERO = AsteroidMath::Vector2(0, 0);

AsteroidMath::Vector2::Vector2()
{
    *this = AsteroidMath::Vector2::ZERO;
    this->updateLength();
}

AsteroidMath::Vector2::Vector2(float x, float y)
{
    this->x = x;
    this->y = y;
    this->updateLength();
}

std::ostream &AsteroidMath::operator<<(std::ostream &out, const AsteroidMath::Vector2 &vector)
{
    out << '(' << vector.getX() << ", " << vector.getY() << ')';
    return out;
}

float AsteroidMath::Vector2::getX() const
{
    return this->x;
}

float AsteroidMath::Vector2::getY() const
{
    return this->y;
}

float AsteroidMath::Vector2::getLength()
{
    if (!(this->isCurrentLengthValid()))
    {
        updateLength();
    }
    return this->length;
}

void AsteroidMath::Vector2::setX(float x)
{
    this->x = x;
    invalidateLength();
}

void AsteroidMath::Vector2::setY(float y)
{
    this->y = y;
    invalidateLength();
}

void AsteroidMath::Vector2::operator=(const sf::Vector2f &sfVector)
{
    this->setX(sfVector.x);
    this->setY(sfVector.y);
}

void AsteroidMath::Vector2::operator+=(const Vector2 &vector)
{
    this->setX(this->x + vector.getX());
    this->setY(this->y + vector.getY());
}

void AsteroidMath::Vector2::operator-=(const Vector2 &vector)
{
    this->setX(this->x - vector.getX());
    this->setY(this->y - vector.getY());
}

void AsteroidMath::Vector2::rotate(float radians)
{
    float newX = this->x * std::cos(radians) - this->y * std::sin(radians);
    float newY = this->x * std::sin(radians) + this->y * std::cos(radians);

    this->setX(newX);
    this->setY(newY);
}

AsteroidMath::Vector2 AsteroidMath::Vector2::limitLength(float limit)
{
    AsteroidMath::Vector2 returnVector = *this;
    if (this->getLength() > limit)
    {
        returnVector /= this->getLength();
        returnVector *= limit;
    }
    return returnVector;
}

void AsteroidMath::Vector2::normalize()
{
    if (this->getLength() != 0)
    {
        float length = this->getLength();
        this->setX(this->x / length);
        this->setY(this->y / length);
    }
}

AsteroidMath::Vector2 AsteroidMath::Vector2::normalized()
{
    if (this->getLength() != 0)
    {
        return {this->x / length, this->y / length};
    }
    else return *this;
}

void AsteroidMath::Vector2::updateLength()
{
    length = sqrt(pow(this->x, 2) + pow(this->y, 2));
}

float AsteroidMath::Vector2::getAngleTo(AsteroidMath::Vector2 &vector)
{
    return acos(this->dotProduct(vector) / (this->getLength() * vector.getLength()));
}

float AsteroidMath::Vector2::dotProduct(const AsteroidMath::Vector2 &vector)
{
    return (this->getX() * vector.getX()) + (this->getY() * vector.getY());
}

bool AsteroidMath::Vector2::isCurrentLengthValid() const
{
    return (!std::isnan(this->length));
}

void AsteroidMath::Vector2::invalidateLength()
{
    this->length = NAN; // Set to NaN
}