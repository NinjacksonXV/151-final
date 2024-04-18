/**
 * @file Button.cpp
 * @author Jacob McKenzie
 * @brief Button class cpp file 
 * @version 0.1
 * @date 2024-04-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "Button.hpp"

Button::Button(std::string s, sf::Vector2f position)
{
    if(!mFont.loadFromFile("VCR_MONO.ttf"))
    {
        std::cout << "Error opening ttf file.\n";
        exit(2);
    }

    mPosition = position;
    setPosition(mPosition);
    mText.setFont(mFont);
    mText.setString(s);
    setSize({1, 1});

}

void Button::setPosition(sf::Vector2f position)
{
    mPosition = position;
    setPosition(lines, mPosition);
}

sf::Vector2f Button::getPosition()
{
    return mPosition;
}

void Button::setSize(sf::Vector2f size)
{
    mSize = size;
}

void Button::setText(std::string s)
{
    mText.setString(s);
}

void Button::setPosition(sf::Vertex lines[], sf::Vector2f position)
{
    lines[0].position = sf::Vector2f(position.x - (mSize.x/2), position.y - (mSize.y/2));
    lines[1].position = sf::Vector2f(position.x + (mSize.x/2), position.y - (mSize.y/2));
    lines[2].position = sf::Vector2f(position.x + (mSize.x/2), position.y + (mSize.y/2));
    lines[3].position = sf::Vector2f(position.x - (mSize.x/2), position.y + (mSize.y/2));
    lines[4].position = lines[0].position;
}

void Button::update(sf::Event &e, sf::RenderWindow &window)
{
    // Get position of mouse
    sf::Vector2i unmappedMouse = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosition = window.mapPixelToCoords(unmappedMouse);

    bool mouseInButton = mousePosition.x >= mPosition.x - (mSize.x/2)
                    && mousePosition.x <= mPosition.x + (mSize.x/2)
                    && mousePosition.y >= mPosition.y - (mSize.y/2)
                    && mousePosition.y <= mPosition.y + (mSize.y/2);
    
    if(e.type == sf::Event::MouseMoved)
    {
        if(mouseInButton)
        {
            mText.setFillColor(mTextHover);
        }
        else
        {
            mText.setFillColor(mTextNormal);
        }
    }

    if(e.type == sf::Event::MouseButtonPressed)
    {
        if(e.mouseButton.button == sf::Mouse::Left)
        {
            if(mouseInButton)
            {
                setPosition({mPosition.x, mPosition.y + 5});
            }
            else
            {
                setPosition(mPosition);
            }
        }
    }
    
    if(e.type == sf::Event::MouseButtonReleased)
    {
        if(e.mouseButton.button == sf::Mouse::Left)
        {
            if(mouseInButton)
            {
                mText.setFillColor(mTextHover);
                setPosition(mPosition);
            }
            else
            {
                mText.setFillColor(mTextNormal);
                setPosition(mPosition);
            }
        }
    }

}