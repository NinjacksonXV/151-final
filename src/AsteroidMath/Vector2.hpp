#include <math.h>

namespace AsteroidMath
{
    class Vector2
    {
        private:
            float x;
            float y;
            float length;
        
        public:
            float getX() const;
            float getY() const;
            float getLength();

            void setX(float x);
            void setY(float y);
            void setLength(float length);

            static const AsteroidMath::Vector2 UP;
            static const AsteroidMath::Vector2 DOWN;
            static const AsteroidMath::Vector2 LEFT;
            static const AsteroidMath::Vector2 RIGHT;
            static const AsteroidMath::Vector2 ZERO;

            Vector2();
            Vector2(float x, float y);
            ~Vector2();
            
            void rotate(float radians);
            void limitLength(float limit);
            void normalize();

            void updateLength();

            bool isCurrentLengthPreCalculated() const;
            void invalidateLength();
    };
};