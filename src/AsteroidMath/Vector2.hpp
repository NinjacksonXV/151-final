#include <math.h>
#include <iostream>

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

            Vector2& operator+=(const Vector2& vector);
            template <typename T>
            Vector2& operator*(const T scalar)
            {
                this-> x *= T;
                this-> y *= T;
            }

            static const AsteroidMath::Vector2 UP;
            static const AsteroidMath::Vector2 DOWN;
            static const AsteroidMath::Vector2 LEFT;
            static const AsteroidMath::Vector2 RIGHT;
            static const AsteroidMath::Vector2 ZERO;

            Vector2();
            Vector2(float x, float y);
            ~Vector2();

            friend std::ostream& operator<<(std::ostream& out, const AsteroidMath::Vector2& vector);
            //TO-DO: Type casting from AsteroidMath::Vector2 to sf::Vector2f
            void rotate(float radians);
            void limitLength(float limit);
            void normalize();

            void updateLength();

            bool isCurrentLengthPreCalculated() const;
            void invalidateLength();
    };
};