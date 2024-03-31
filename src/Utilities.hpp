#pragma once
#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

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

float toDegrees(float radians)
{
    return radians * (180 / M_PI);
}