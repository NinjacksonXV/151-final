#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Button.hpp"
#include "GameObject.hpp"
#include "Text.hpp"


class GUI : public sf::Drawable
{
public:
    void addButton(std::string s, sf::Vector2f position, sf::Vector2f size);
    void removeAllButtons(){buttons.clear();};
    void addText(std::string s, sf::Vector2f position, unsigned size, sf::Color fillColor);
    void removeAllTexts(){texts.clear();};

    virtual void update(sf::Event &e, sf::RenderWindow &window);
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
private:
    sf::RenderWindow window;
    int selection;
    sf::Font mFont;
    sf::Text mText;
    std::vector<Button*> buttons;
    std::vector<Text*> texts;
};

#endif