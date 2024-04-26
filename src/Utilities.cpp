#include "Utilities.hpp"

std::ostream &operator<<(std::ostream &out, const sf::Transform &transform)
{
    for (int i = 0; i != 16; i += 4)
    {
        out << '(';
        for (int j = 0; j < 4; j++)
        {
            out << transform.getMatrix()[i + j];
            if (j == 3)
                break;
            else
                out << ", ";
        }
        out << ")\n";
    }
    out << '\n';
    return out;
}

std::ostream &operator<<(std::ostream &out, const sf::Color &color)
{
    out << '(' << color.r << ", " << color.g << ", " << color.b << ')'; 
    return out;
}

float toDegrees(float radians)
{
    return radians * (180 / M_PI);
}

AsteroidMath::Vector2 asAMVector2(sf::Vector2f vector2f)
{
    return {vector2f.x, vector2f.y};
}
