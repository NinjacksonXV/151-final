#pragma once
#include <string>
#include <SFML/Graphics.hpp>

struct ColorPalette
{
    std::string name;
    sf::Color primary;
    sf::Color secondary;
    sf::Color tertiary;

    static const ColorPalette basic;
    static const ColorPalette bumblebit;
    static const ColorPalette coldlight;
    static const ColorPalette candy;
    static const ColorPalette rust;
    static const ColorPalette mushroom;
};
