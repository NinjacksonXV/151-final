#pragma once
#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

/**
 * @brief Outputs an `sf::Transform` in a 4x4 matrix in the console.  
 * 
 * @param transform Transform to display.
 */
void displayTransform(sf::Transform transform)
{
    for (int i = 0; i != 16; i += 4)
    {
        std::cout << '(';
        for (int j = 0; j < 4; j++)
        {
            std::cout << transform.getMatrix()[i + j];
            if (j == 4)
                break;
            else
                std::cout << ", ";
        }
        std::cout << ")\n";
    }
    std::cout << '\n';
}

/**
 * @brief Returns the provided radians as degrees, which is required for most SFML `rotate()` functions. 
 * 
 * @param radians Input radians to be converted to degrees.
 * @return float Output degrees.
 */
float toDegrees(float radians)
{
    return radians * (180 / M_PI);
}