#include "Transform.hpp"

void AsteroidMath::Transform::rotate(float radians)
{
    this->x.rotate(radians);
    this->y.rotate(radians);
}