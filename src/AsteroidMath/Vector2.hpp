#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>
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

        // void operator=(const AsteroidMath::Vector2 &sfVector);
        // void operator=(const sf::Vector2f &sfVector);
        AsteroidMath::Vector2 operator=(const sf::Vector2f &sfVector);
        void operator+=(const Vector2 &vector);
        void operator-=(const Vector2 &vector);
        Vector2 operator-(const Vector2 &vector);

        // auto expands to template argument types in C++ 20
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

        /**
         * @brief Get the distance to another vector
         *
         * @param vector
         * @return float
         */
        float getDistanceTo(const sf::Vector2f &vector);

        AsteroidMath::Vector2 operator*(auto scalar)
        {
            return {this->x * static_cast<float>(scalar), this->y * static_cast<float>(scalar)};
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

        /**
         * @brief Rotate the vector.
         *
         * @param radians
         */
        void rotate(float radians);

        /**
         * @brief Returns the vector with its length limited.
         *
         * @param limit
         * @return AsteroidMath::Vector2
         */
        AsteroidMath::Vector2 limitLength(float limit);

        /**
         * @brief Normalize the vector.
         *
         */
        void normalize();

        /**
         * @brief Return the vector as its normalized version.
         *
         * @return AsteroidMath::Vector2
         */
        AsteroidMath::Vector2 normalized();

        /**
         * @brief Get the angle in radians to another vector
         * 
         * @param vector 
         * @return float 
         */
        float getAngleTo(AsteroidMath::Vector2 &vector);

        /**
         * @brief Return the dot product of this vector and another vector.
         * vector1.dotProduct(vector2) == vector2.dotProduct(vector1)
         * 
         * @param vector 
         * @return float 
         */
        float dotProduct(const AsteroidMath::Vector2 &vector);

    private:
        void updateLength();
        bool isCurrentLengthValid() const;
        void invalidateLength();
    };
    std::ostream &operator<<(std::ostream &out, const AsteroidMath::Vector2 &vector);
};