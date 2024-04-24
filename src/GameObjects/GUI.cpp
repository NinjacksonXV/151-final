#include "GUI.hpp"

void GUI::addButton(std::string s, sf::Vector2f position, sf::Vector2f size)
{
    Button *button = new Button(s, position, size);
    buttons.push_back(button);
}

void GUI::addText(std::string s, sf::Vector2f position, unsigned size, sf::Color fillColor)
{
    Text *text = new Text(s, position, size, fillColor);
    texts.push_back(text);
}

void GUI::changeText(std::string newString, int index)
{
    texts[index]->setText(newString);
}

void GUI::changeText(int newNumber, int index)
{
    std::string newString = std::to_string(newNumber);
    texts[index]->setText(newString);
}

void GUI::update(sf::Event &e, sf::RenderWindow &window)
{
    for(std::size_t i = 0; i < buttons.size(); i++)
    {
        buttons[i]->update(e, window);
    }
}

void GUI::draw(sf::RenderTarget &target, sf::RenderStates states) const 
{
    for(std::size_t i = 0; i < buttons.size(); i++)
    {
        buttons[i]->draw(target, states);
    }

    for(std::size_t i = 0; i < texts.size(); i++)
    {
        texts[i]->draw(target, states);
    }

}
