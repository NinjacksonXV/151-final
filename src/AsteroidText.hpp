#include "Colorable.hpp"
#include <SFML/Graphics.hpp>

/**
 * @brief Text that is Colorable
 * 
 */
class AsteroidText : public sf::Text, public Colorable
{
    void setColorPalette(const ColorPalette &colorPalette)
    {
        this->setFillColor(colorPalette.secondary);
    }
};