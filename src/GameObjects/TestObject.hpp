#include "Object2D.hpp"

class TestObject : public Object2D
{
public:
    TestObject(sf::Vector2f pos)
    {
        this->setPosition(pos);
        circle.setRadius(20);
    }

private:
    sf::CircleShape circle;
    virtual void onDraw(sf::RenderTarget &target, const sf::Transform &transform) const
    {
        target.draw(circle, transform);
    };
};