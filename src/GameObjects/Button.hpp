/**
 * @file Button.hpp
 * @author Jacob McKenzie
 * @brief  Button header file
 * @version 0.1
 * @date 2024-04-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "GameObject.hpp"

enum state
{
    NORMAL,
    HOVERED,
    CLICKED
};

class Button : public GameObject
{
public:
    Button(std::string s, sf::Vector2f position);
    ~Button();
    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition();
    void setSize(sf::Vector2f size);
    void setText(std::string s);
    void setColorTextNormal(sf::Color textNormalColor){mTextNormal = textNormalColor;};
    void setColorTextHover(sf::Color textHoverColor){mTextHover = textHoverColor;};
    void update(sf::Event &e, sf::RenderWindow &window);
    virtual void onDraw(sf::RenderTarget& target, const sf::Transform &transform) const;

private:

    void setPosition(sf::Vertex lines[], sf::Vector2f position);
    
    
    sf::Vector2f mSize;

    //Button
    sf::Vertex lines[5];
    sf::Vector2f mPosition;

    //Text 
    sf::Text mText;
    sf::Font mFont;
    sf::Color mTextNormal = sf::Color::White;
    sf::Color mTextHover = sf::Color(220, 220, 220);

    

};

