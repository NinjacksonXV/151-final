#include "../Game.hpp"
#include "Object2D.hpp"
#include "../Utilities.hpp"

class GameplayShape : public Object2D, public sf::ConvexShape
{
public:
    sf::FloatRect getGlobalBounds() { return rect; };
private:
    std::vector<sf::Vector2f> normals;
    std::vector<CollisionLayer> collisionLayers;
    void calculateNormals();
    void onDraw(sf::RenderTarget &target, const sf::Transform &transform) const
    {
        rect = transform.transformRect(getLocalBounds());
        std::cout << "Drawing\n";
        target.draw(*this, transform);
        std::cout << "Drew";
    };

protected:
    mutable sf::FloatRect rect;

};