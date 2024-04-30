#pragma once
#include <list>
#include "Object2D.hpp"
#include "../Utilities.hpp"

extern sf::RenderTarget const *windowAccessor;

class Bullet : public Object2D, public sf::ConvexShape
{
public:
    using Object2D::getPosition;
    Bullet(sf::Vector2f rotation, sf::Vector2f position);
    void init() override{};
    void update(float deltaTime) override;

    AsteroidMath::Vector2 getHeading() {return asAMVector2(travelRotation);}
    void impact();
    bool queueDelete = false;
    bool collidedThisFrame = false;
    
private:
    sf::Vector2f travelRotation;
    short int offscreenCount;
    void onDraw(sf::RenderTarget &target, const sf::Transform &transform) const
    {
        target.draw(*this, this->Object2D::getTransform());
    };

};

extern std::list<Bullet *> *bulletAccessor;