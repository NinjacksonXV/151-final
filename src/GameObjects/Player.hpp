#include "Object2D.hpp"

extern sf::RenderTarget const *windowAccessor;

class Player : public Object2D
{
private:
    void update(float delta) override;

public:
    void init() override;
};

class PlayerShape : public Object2D
{

public:
    void init() override
    {
        shape.setPoint(0, {30, -10});
        shape.setPoint(1, {0, 0});
        shape.setPoint(2, {-30, -10});
        shape.setPoint(3, {0, 40});
        shape.setFillColor(sf::Color::Black);
        shape.setOutlineColor(sf::Color::White);
        shape.setOutlineThickness(4.0f);
    }

private:
    sf::ConvexShape shape{4};
    void onDraw(sf::RenderTarget &target, const sf::Transform &transform) const
    {
        target.draw(this->shape, transform);
    };
};

// TO-DO: Move this into its own class

class TempStars : public Object2D
{
public:
    void init() override
    {
        std::cout << "What";
        rect = sf::RectangleShape(sf::Vector2f(windowAccessor->getSize().x, windowAccessor->getSize().y));
        if (!shader.loadFromFile("stars.frag", sf::Shader::Fragment))
            std::cout << "Didn't load shader\n";
        shader.setUniform("u_resolution", sf::Vector2f(1920, 1080));
        setPosition({-(1920 / 2), -(1080 / 2)});

        renderState.shader = &shader;
    }

private:
    sf::RectangleShape rect;
    
    mutable sf::Shader shader;
    mutable sf::RenderStates renderState;

    void onDraw(sf::RenderTarget &target, const sf::Transform &transform) const
    {
        shader.setUniform("position", sf::Vector2f(getPosition().x, getPosition().y  * -1.)); // SFML y-axis is inverted
        renderState.transform = this->getTransform();
        target.draw(rect, renderState);
    };
};