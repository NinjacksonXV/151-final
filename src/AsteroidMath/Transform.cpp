#include "Transform.hpp"

void AsteroidMath::Transform::rotate(float radians)
{
    this->x.rotate(radians);
    this->y.rotate(radians);
}

AsteroidMath::Vector2 AsteroidMath::Transform::operator*(const AsteroidMath::Vector2& vector)
{
    AsteroidMath::Vector2 returnVector;
    returnVector.setX((vector.getX() * this->x.getX()) + (vector.getY() * this->x.getY()));
    returnVector.setY((vector.getX() * this->y.getX()) + (vector.getY() * this->y.getY()));
    return AsteroidMath::Vector2();
}
