#include <math.h>
#include <iostream>
#include <SFML/System.hpp>

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

        AsteroidMath::Vector2 &operator+=(const Vector2 &vector);
        template <typename T>
        AsteroidMath::Vector2 &operator*(const T scalar)
        {
            this->x *= static_cast<float>(scalar);
            this->y *= static_cast<float>(scalar);
            return *this;
        }

        static const AsteroidMath::Vector2 UP;
        static const AsteroidMath::Vector2 DOWN;
        static const AsteroidMath::Vector2 LEFT;
        static const AsteroidMath::Vector2 RIGHT;
        static const AsteroidMath::Vector2 ZERO;

        Vector2();
        Vector2(float x, float y);
        // ~Vector2();

        friend std::ostream &operator<<(std::ostream &out, const AsteroidMath::Vector2 &vector);
        operator sf::Vector2f() const
        {
            return sf::Vector2f(this->getX(), this->getY());
        }
        operator sf::Vector2f *() const
        {
            return reinterpret_cast<sf::Vector2f *>(const_cast<Vector2 *>(this));
        }
        void rotate(float radians);
        void limitLength(float limit);
        void normalize();

        void updateLength();

        float getAngleTo(const AsteroidMath::Vector2 &vector);
        float dotProduct(const AsteroidMath::Vector2 &vector); 

        bool isCurrentLengthPreCalculated() const;
        void invalidateLength();
    };
    std::ostream &operator<<(std::ostream &out, const AsteroidMath::Vector2 &vector);
};