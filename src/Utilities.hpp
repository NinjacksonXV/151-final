#pragma once
#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "AsteroidMath/Vector2.hpp"

/**
 * @brief Operator overload for an `sf::Vector2`
 */
template <typename T>
std::ostream &operator<<(std::ostream &out, const sf::Vector2<T> &vector)
{
    out << '(' << vector.x << ", " << vector.y << ')';
    return out;
}

/**
 * @brief Operator overload for an `sf::Rect`

 */
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
 * @brief Outputs a color to the console.
 *
 * @param color Color to display
 */
std::ostream &operator<<(std::ostream &out, const sf::Color &color);

/**
 * @brief Returns the provided radians as degrees, which is required for most SFML `rotate()` functions.
 *
 * @param radians Input radians to be converted to degrees.
 * @return float Output degrees.
 */
float toDegrees(float radians);

/**
 * @brief Returns the sign of a given numerical.
 *
 * @param val Number to return the sign of
 * @return int Returns either 1, -1, or zero if the number provided is 0.
 * @author https://stackoverflow.com/a/4609795
 *
 */
template <typename T>
int sign(T val)
{
    return (T(0) < val) - (val < T(0));
}

AsteroidMath::Vector2 asAMVector2(sf::Vector2f vector2f);