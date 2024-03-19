#include "Vector2.hpp"
namespace AsteroidMath
{
    class Transform
    {
        public:
            static const Transform IDENTITY;

            void rotate(float radians); //simply rotate the two unit vectors

            AsteroidMath::Vector2 operator*(const AsteroidMath::Vector2& vector); 

        private:
        // for now, these should always be unit vectors.
        AsteroidMath::Vector2 x = Vector2::UP;
        AsteroidMath::Vector2 y = Vector2::RIGHT;
    };
}