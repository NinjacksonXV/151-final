#pragma once
#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

template <typename T>
std::ostream &operator<<(std::ostream &out, const sf::Vector2<T> &vector)
{
    out << '(' << vector.x << ", " << vector.y << ')';
    return out;
}
template <typename T>
std::ostream &operator<<(std::ostream &out, const sf::Rect<T> rect)
{
    out << "T: " << rect.top << " L: " << rect.left << "\n";
    out << "W: " << rect.width << " H: " << rect.height << '\n';
    return out;
}
/**
 * @brief Outputs an `sf::Transform` in a 4x4 matrix in the console.
 *
 * @param transform Transform to display.
 */
std::ostream &operator<<(std::ostream &out, const sf::Transform &transform);

/**
 * @brief Returns the provided radians as degrees, which is required for most SFML `rotate()` functions.
 *
 * @param radians Input radians to be converted to degrees.
 * @return float Output degrees.
 */
float toDegrees(float radians);
