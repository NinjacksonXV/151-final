#include "Text.hpp"

Text::Text(std::string s, sf::Vector2f position, unsigned size, sf::Color color)
{
    if(!mFont.loadFromFile("HelvetiPixel.ttf"))
    {
        std::cout << "Error opening font file.\n";
        exit(2);
    }

    mText.setFont(mFont);
    mText.setString(s);

    mTextColor = color;
    mText.setFillColor(mTextColor);

    mSize = size;
    mText.setCharacterSize(mSize);
    mText.setOrigin(mText.getGlobalBounds().width/2, mText.getGlobalBounds().height/2);

    mPosition = position;
    mText.setPosition(mPosition.x, mPosition.y - mSize/2);
}

void Text::setPosition(sf::Vector2f position)
{
    mPosition = position;

    mText.setPosition(mPosition.x, mPosition.y - mSize/2);
}

void Text::setColor(sf::Color color)
{
    mTextColor = color;
    mText.setFillColor(mTextColor);
}

void Text::setText(std::string s)
{
    mText.setString(s);
}

void Text::setSize(unsigned size)
{
    mSize = size;
    mText.setCharacterSize(mSize);
}

void Text::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mText, states);
}