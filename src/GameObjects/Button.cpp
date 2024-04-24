#include "Button.hpp"

Button::Button(std::string s, sf::Vector2f position, sf::Vector2f size)
{
    mButton.setSize(size);
    mButton.setOrigin(mButton.getSize().x/2, mButton.getSize().y/2);
    mPosition = position;
    mButton.setPosition(mPosition);

    mButton.setFillColor(sf::Color (0, 0, 0, 0)); //Change alpha to 0

    if(!mFont.loadFromFile("HelvetiPixel.ttf"))
    {
        std::cout << "Error opening font file.\n";
        exit(2);
    }

    mText.setFont(mFont);
    mText.setString(s);

    unsigned int fontSize = mButton.getGlobalBounds().height;
    mText.setCharacterSize(fontSize);


    mText.setOrigin(mText.getGlobalBounds().width/2, mText.getGlobalBounds().height/2);
    mText.setPosition(mPosition.x, mPosition.y - fontSize/2);

    mTextNormal = sf::Color::White;
    mTextHover = sf::Color::Red;

    isSelected = false;

    mTriangle.setRadius(10);
    mTriangle.setOrigin(mTriangle.getRadius(), mTriangle.getRadius());
    mTriangle.setFillColor(sf::Color::Red);

    mTriangle.setPointCount(3);
    mTriangle.setRotation(90);
    mTriangle.setScale(1, 3);

    mTriangle.setPosition(mPosition.x - (mButton.getSize().x/2), mPosition.y);

}

void Button::update(sf::Event &e, sf::RenderWindow &window)
{
    sf::Vector2i mPos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosition = window.mapPixelToCoords(mPos);
    bool mouseInButton = mousePosition.x >= mButton.getPosition().x - mButton.getGlobalBounds().width/2
                        && mousePosition.x <= mButton.getPosition().x + mButton.getGlobalBounds().width/2
                        && mousePosition.y >= mButton.getPosition().y - mButton.getGlobalBounds().height/2
                        && mousePosition.y <= mButton.getPosition().y + mButton.getGlobalBounds().height/2;
    
    if(e.type == sf::Event::MouseMoved)
    {
        if(mouseInButton)
        {
            mText.setFillColor(mTextHover);
            mTriangle.setPosition(mPosition.x - (mButton.getSize().x/2), mPosition.y);
            isSelected = true;
        }
        else
        {
            mText.setFillColor(mTextNormal);
            isSelected = false;
        }
    }

    if(e.type == sf::Event::MouseButtonPressed)
    {
        if(e.mouseButton.button == sf::Mouse::Left)
        {
            if(mouseInButton)
            {
                //play sound 
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
                mTriangle.setPosition(mPosition.x - (mButton.getSize().x/2), mPosition.y);
                isSelected = true;
            }
            else
            {
                mText.setFillColor(mTextNormal);
                isSelected = false;
            }
        }
    }
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mButton, states);
    target.draw(mText, states);
    if(isSelected)
    {
        target.draw(mTriangle, states);
    }
}

void Button::setText(std::string s)
{
    unsigned int fontSize = mButton.getGlobalBounds().height/2;
    mText.setCharacterSize(fontSize);

    mText.setOrigin(mText.getGlobalBounds().width/2, mText.getGlobalBounds().height/2);
    mText.setPosition(mPosition.x, mPosition.y - fontSize/4);
    mText.setString(s);
}

void Button::setPosition(sf::Vector2f position)
{
    mPosition = position;
    mButton.setPosition(mPosition);
    unsigned int fontSize = mButton.getGlobalBounds().height/2;
    mText.setPosition(mPosition.x, mPosition.y - fontSize/4);
}

void Button::setSize(sf::Vector2f size)
{
    sf::Vector2f imageSize = mButton.getSize();
    mButton.setOrigin(imageSize.x/2, imageSize.y/2);
    
    unsigned int fontSize = mButton.getGlobalBounds().height/2;
    mText.setCharacterSize(fontSize);

    mText.setOrigin(mText.getGlobalBounds().width/2, mText.getGlobalBounds().height/2);
    mText.setPosition(mPosition.x, mPosition.y - fontSize/4);
}

void Button::setColor(sf::Color btnColor)
{
    mButtonColor = btnColor;
    mButton.setFillColor(mButtonColor);
}

void Button::setOutlineColor(sf::Color color, unsigned thickness)
{
    mButton.setOutlineThickness(thickness);
    mButton.setOutlineColor(color);
}