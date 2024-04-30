#include "MenuButton.hpp"

MenuButton::MenuButton(std::string string, sf::Font font)
{
    this->text.setFont(font);
    this->text.setString(string);
    this->text.setCharacterSize(40);
    this->text.setOrigin(this->text.getLocalBounds().width / 2.f, this->text.getLocalBounds().height / 2.f);
    rectangleShape.setSize({350, 120});
    this->setOrigin(rectangleShape.getLocalBounds().width / 2.f, rectangleShape.getLocalBounds().height / 2.f);
    setColorPalette(Game::getColorPalette());
    rectangleShape.setOutlineThickness(4.f);
    text.setPosition(1080.f, 720.f);
}

void MenuButton::setColorPalette(const ColorPalette &colorPalette)
{
    this->text.setFillColor(colorPalette.secondary);
    this->rectangleShape.setFillColor(colorPalette.primary);
    this->rectangleShape.setOutlineColor(colorPalette.tertiary);
}

sf::FloatRect MenuButton::getGlobalBounds()
{
    return this->getTransform().transformRect(rectangleShape.getLocalBounds());
}

bool MenuButton::isPressed(const sf::Window &window)
{
    return this->getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

void MenuButton::onDraw(sf::RenderTarget &target, const sf::Transform &transform) const
{
    text.setString("PLAY");
    target.draw(rectangleShape, this->getTransform());
    target.draw(text);
}
