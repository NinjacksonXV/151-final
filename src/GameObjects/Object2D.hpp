#pragma once
#include "GameObject.hpp"
#include "../AsteroidMath/Vector2.hpp"

class Object2D : public GameObject, public sf::Transformable
{
public:
    virtual void draw(sf::RenderTarget &target) const override;
    virtual void draw(sf::RenderTarget &target, const sf::Transform &parentTransform) const;
    virtual void update(float delta) override;

protected:
    Object2D *parent;
    std::vector<Object2D *> children;

private:
    virtual void onDraw(sf::RenderTarget &target, const sf::Transform &transform) const {};
};