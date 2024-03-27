#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "AsteroidMath/Vector2.hpp"

class Object2D : public GameObject
{
    public:
    AsteroidMath::Vector2 getPosition() {return position;};
    AsteroidMath::Vector2 getVelocity() {return velocity;};


    protected:
    AsteroidMath::Vector2 position = AsteroidMath::Vector2::ZERO;
    sf::Transform transform = sf::Transform::Identity;
    AsteroidMath::Vector2 velocity = AsteroidMath::Vector2::ZERO;
    
    void rotate(float radians);
};