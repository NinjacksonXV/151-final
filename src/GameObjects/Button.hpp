#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Button : public sf::Drawable
{
public:
    Button(std::string s, sf::Vector2f position, sf::Vector2f size);
    ~Button(){};
    
    void setPosition(sf::Vector2f position);
    void setSize(sf::Vector2f size);
    void setColor(sf::Color btnColor);
    void setText(std::string s);
    void setColorText(sf::Color textNormalColor){mTextNormal = textNormalColor;};
    void setColorTextHover(sf::Color textHoverColor){mTextHover = textHoverColor;};
    void setOutlineColor(sf::Color color, unsigned thickness);

    sf::Vector2f getPosition(){return mPosition;};
    sf::Vector2f getDimensions(){return sf::Vector2f(mButton.getGlobalBounds().width, mButton.getGlobalBounds().height);};

    virtual void update(sf::Event &e, sf::RenderWindow &window);
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    sf::RectangleShape mButton;
    sf::Color mButtonColor;
    sf::Vector2f mPosition;
    
    bool isSelected;
    sf::CircleShape mTriangle;

    sf::Text mText;
    sf::Font mFont;
    sf::Color mTextNormal = sf::Color::White;
    sf::Color mTextHover = sf::Color::Red;
    //sf::Color mTextClicked;

};


#endif