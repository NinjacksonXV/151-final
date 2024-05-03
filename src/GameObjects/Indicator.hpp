#include "Object2D.hpp"

/**
 * @brief Red dot used for testing
 * 
 */
class Indicator : public Object2D, public sf::CircleShape
{
public:
    Indicator(sf::Vector2f position)
    {
        this->Object2D::setPosition(position);
        setPointCount(10);
        setRadius(10);
        this->Object2D::setOrigin({5, -5});
        setFillColor(sf::Color::Red);
        gameObjectAccessor->push_back(this);
    };

private:
    void onDraw(sf::RenderTarget &target, const sf::Transform &) const 
    {
        target.draw(*this, this->Object2D::getTransform());
    }
};