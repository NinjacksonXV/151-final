#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

#define M_TAU (M_PI * 2.0f)
int main()
{
    size_t p = 10;
    sf::ConvexShape asteroidTest(p);
    asteroidTest.setPoint(0, {-3.0f, 0});
    float a = 10;
    for (size_t i = 0; i < p; i++)
    {
        sf::Vector2f point(cos(M_TAU * (static_cast<float>(i) / static_cast<float>(p))), sin(M_TAU * (static_cast<float>(i) / static_cast<float>(p))));
        a += 40;
        point *= a;
        asteroidTest.setPoint(i, point);

    }
    asteroidTest.setPosition(500, 500);

    asteroidTest.setOutlineColor(sf::Color::White);
    asteroidTest.setOutlineThickness(3);

    auto window = sf::RenderWindow{ { 1920u, 1080u }, "CMake SFML Project" };
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.draw(asteroidTest);
        window.display();
    }
}