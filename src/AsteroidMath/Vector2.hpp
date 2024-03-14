#include <math.h>

namespace AsteroidMath
{
    class Vector2
    {
        public:
            float x;
            float y;
            float length;
            
            static const AsteroidMath::Vector2 UP;
            static const AsteroidMath::Vector2 DOWN;
            static const AsteroidMath::Vector2 LEFT;
            static const AsteroidMath::Vector2 RIGHT;
            static const AsteroidMath::Vector2 ZERO;


            Vector2();
            Vector2(float x, float y);
            ~Vector2();
            
            void rotate(float radians);
            void setLength(float length);
            void limitLength(float limit);

        private:
            void updateLength();
    };
};