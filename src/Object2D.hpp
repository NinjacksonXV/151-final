#include <GameObject.hpp>

class Object2D : public GameObject
{
    public:
    AsteroidMath::Vector2 getPosition() {return position;};
    AsteroidMath::Vector2 getVelocity() {return velocity;};


    protected:
    AsteroidMath::Vector2 position = AsteroidMath::Vector2::ZERO;
    AsteroidMath::Transform transform = AsteroidMath::Transform::IDENTITY;
    AsteroidMath::Vector2 velocity = AsteroidMath::Vector2::ZERO;
    
    void rotate(float radians);
};