#include "AccelerationLine.hpp"

float decaySpeed = 40.f;

AccelerationLine::AccelerationLine(sf::Vector2f position, sf::Vector2f rotation)
{
    this->Object2D::setPosition(position);
    this->setPointCount(4);
    this->setPoint(0, {-20, 2});
    this->setPoint(1, { 20, 2});
    this->setPoint(2, { 20, -2});
    this->setPoint(3, {-20, -2});
    this->Object2D::rotate(toDegrees(atan(rotation.y / rotation.x)) + 90);
    gameObjectAccessor->push_back(this);
}

void AccelerationLine::update(float delta)
{
    this->setPoint(0, {getPoint(0).x + delta * decaySpeed, getPoint(0).y - delta});
    this->setPoint(1, {getPoint(1).x - delta * decaySpeed, getPoint(1).y - delta});
    this->setPoint(2, {getPoint(2).x - delta * decaySpeed, getPoint(2).y + delta});
    this->setPoint(3, {getPoint(3).x + delta * decaySpeed, getPoint(3).y + delta});

    if (this->getPoint(1).x <= 0.f)
        queueDelete = true;
}

void AccelerationLine::setColorPalette(const ColorPalette &palette)
{
    this->setFillColor(palette.secondary);
}
