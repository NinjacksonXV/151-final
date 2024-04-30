#include <SFML/Graphics.hpp>
#include "../../Colorable.hpp"
#include "../Object2D.hpp"
#include "../../Game.hpp"

class MenuButton : public Colorable, public Object2D
{
public:
    MenuButton(std::string text, sf::Font &font);
    sf::Text text;
    void setColorPalette(const ColorPalette &colorPalette) override;
    sf::FloatRect getGlobalBounds();
    bool isPressed(const sf::Window &window);
private: 
    bool wasPressed = false;
    sf::RectangleShape rectangleShape;
    void onDraw(sf::RenderTarget &target, const sf::Transform &transform) const;
};