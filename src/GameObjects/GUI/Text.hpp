#ifndef TEXT_HPP
#define TEXT_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Text : public sf::Drawable
{
public:
    Text(std::string s, sf::Vector2f position, unsigned size, sf::Color color);
    void setPosition(sf::Vector2f position);
    void setColor(sf::Color color);
    void setText(std::string s);
    void setSize(unsigned size);
    
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    sf::Text mText;
    unsigned mSize;
    sf::Color mTextColor;
    sf::Vector2f mPosition;
    sf::Font mFont;
};


#endif