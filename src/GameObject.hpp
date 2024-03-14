
#include "AsteroidMath/Transform.hpp"
class GameObject
{
    public:
        AsteroidMath::Transform transform = AsteroidMath::Transform::IDENTITY; 
        void rotate(float radians);

    private:
        
        virtual void update(float deltaTime) = 0;
};