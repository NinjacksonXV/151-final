#include "Vector2.hpp"
namespace AsteroidMath
{
    class Transform
    {
        public:
            static const Transform IDENTITY;

            void rotate(float radians); //simply rotate the two unit vectors

            Transform& operator*(AsteroidMath::Vector2 vector); //matrix multiplication


        private:
        // for now, these should always be unit vectors.  
        AsteroidMath::Vector2 x = Vector2(1, 0);
        AsteroidMath::Vector2 y = Vector2(0, 1);
    };
}