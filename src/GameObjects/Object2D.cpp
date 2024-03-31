#include "Object2D.hpp"

void Object2D::draw(sf::RenderTarget &target) const
{

    onDraw(target, this->getTransform());
    for (std::size_t i = 0; i < children.size(); ++i)
        children[i]->draw(target, this->getTransform());
}

void Object2D::draw(sf::RenderTarget &target, const sf::Transform &parentTransform) const
{
    // From SFML transform tutorial
    // combine the parent transform with the Object2D's one
    sf::Transform combinedTransform = parentTransform * getTransform();

    // let the object draw itself
    onDraw(target, combinedTransform);

    // draw its children
    for (std::size_t i = 0; i < children.size(); ++i)
        children[i]->draw(target, combinedTransform);
}

void Object2D::update(float delta)
{
    for (Object2D *child : children)
    {
        child->update(delta);
    }
}
