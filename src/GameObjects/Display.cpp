/**
 * @file Display.cpp
 * @author Jacob McKenzie
 * @brief 
 * @version 0.1
 * @date 2024-04-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "Display.hpp"

Display::Display(std::string text, sf::Vector2f position, sf::Font font)
{
    mText.setString(text);
    mText.setFont(font);
    mPosition = position;
}

void Display::setPosition(sf::Vector2f position)
{
    mText.setPosition(position);
}

void Display::setText(std::string text)
{
    mText.setString(text);
}

void Display::setCharacterSize(int size)
{
    mText.setCharacterSize(size);
}

void Display::setFont(sf::Font font)
{
    mText.setFont(font);
}