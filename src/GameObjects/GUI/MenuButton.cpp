#include "MenuButton.hpp"

MenuButton::MenuButton(std::string string, sf::Font &font)
{
    this->text.setFont(font);
    this->text.setString(string);
    this->text.setCharacterSize(45);
    std::cout << text.getLocalBounds().width << ", " << text.getLocalBounds().height << '\n';
    this->text.setOrigin(this->text.getLocalBounds().width / 2.f, this->text.getLocalBounds().height / 2.f + 10.f);
    rectangleShape.setSize({350, 120});
    this->setOrigin(rectangleShape.getLocalBounds().width / 2.f, rectangleShape.getLocalBounds().height / 2.f);
    setColorPalette(Game::getColorPalette());
    text.setPosition(this->getOrigin());
    rectangleShape.setOutlineThickness(4.f);
}

void MenuButton::setColorPalette(const ColorPalette &colorPalette)
{
    this->text.setFillColor(colorPalette.secondary);
    this->rectangleShape.setFillColor(colorPalette.primary);
    this->rectangleShape.setOutlineColor(colorPalette.secondary);
}

sf::FloatRect MenuButton::getGlobalBounds()
{
    return this->getTransform().transformRect(rectangleShape.getLocalBounds());
}

bool MenuButton::isPressed(const sf::Window &window)
{
    if (this->getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        if (wasPressed)
            return false;
        else
        {
            wasPressed = true;
            return true;
        }
    }
    else
    {
        wasPressed = false;
        return false;
    }
    // return this->getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

void MenuButton::onDraw(sf::RenderTarget &target, const sf::Transform &transform) const
{
    target.draw(rectangleShape, transform);
    target.draw(text, transform);
}
