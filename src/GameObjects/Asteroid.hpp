#pragma once

#include "../Utilities.hpp"
#include "GameplayShape.hpp"

extern sf::RenderTarget const *windowAccessor;

class Asteroid : public GameplayShape
{
public:
    Asteroid(std::vector<sf::Vector2f> points, sf::Vector2f position);
    Asteroid(unsigned int size);
    Asteroid(unsigned int size, sf::Vector2f position);
    void setColorPalette(const ColorPalette &colorPalette);
    void update(float delta) override;

    void impact(sf::Vector2f position, size_t point1, size_t point2);
    void impact();
    void setSize(int size) {this->size = size;}
    bool queueDelete = false;
private:
    unsigned int size; 
    // void split();
    mutable sf::FloatRect rect;
    sf::Vector2f calculateCentroid();

    // void generatePolygon();
    // void generateValtrPolygon();
    void circumCirclePolygon();
};
extern std::list<Asteroid *> *asteroidAccessor;