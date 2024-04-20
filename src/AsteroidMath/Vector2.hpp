#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#pragma once

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

        // void operator=(const AsteroidMath::Vector2 &sfVector);
        void operator=(const sf::Vector2f &sfVector);
        void operator+=(const Vector2 &vector);
        void operator-=(const Vector2 &vector);
        AsteroidMath::Vector2 operator*(auto scalar) const
        {
            // AsteroidMath::Vector2 returnVector(this->x * static_cast<float>(scalar), this->y * static_cast<float>(scalar));
            return {this->x * static_cast<float>(scalar), this->y * static_cast<float>(scalar)};
        }

        void operator*=(auto scalar)
        {
            this->setX(this->x * static_cast<float>(scalar));
            this->setY(this->y * static_cast<float>(scalar));
        }
        AsteroidMath::Vector2 operator/(auto scalar) const
        {
            return {this->x / static_cast<float>(scalar), this->y / static_cast<float>(scalar)};
        }
        void operator/=(auto scalar)
        {
            this->setX(this->x / static_cast<float>(scalar));
            this->setY(this->y / static_cast<float>(scalar));
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
            // This is to make sure that the X and Y values of sf::Vector2f and Vector2 line up.
            static_assert(offsetof(sf::Vector2f, x) == offsetof(Vector2, x),
                          "Field 'x' is misaligned");
            static_assert(offsetof(sf::Vector2f, y) == offsetof(Vector2, y),
                          "Field 'y' is misaligned");
            return reinterpret_cast<sf::Vector2f *>(const_cast<Vector2 *>(this));
        }

        void rotate(float radians);
        AsteroidMath::Vector2 limitLength(float limit);
        void normalize();
        AsteroidMath::Vector2 normalized();


        void updateLength();

        float getAngleTo(AsteroidMath::Vector2 &vector);
        float dotProduct(const AsteroidMath::Vector2 &vector);

        // Functions to add:
        // Vector2 reflect(Vector2 normal)
        // {
        //     return 2.0f * normal * this->dot(normal) - *this;
        // };
        bool isCurrentLengthValid() const;
        void invalidateLength();
    };
    std::ostream &operator<<(std::ostream &out, const AsteroidMath::Vector2 &vector);
};