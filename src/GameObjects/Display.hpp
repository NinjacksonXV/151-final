#pragma once
#include "GameObject.hpp"

class Display : public GameObject
{
public:
    Display(std::string text, sf::Vector2f position, sf::Font font);
    ~Display();
    void setPosition(sf::Vector2f position);
    void setText(std::string text);
    void setCharacterSize(int size);
    void setFont(sf::Font font);

    virtual void onDraw(sf::RenderTarget& target, const sf::Transform &transform) const;
private:
    sf::Vector2f mPosition;
    sf::Text mText;
    sf::Font mFont;

};

