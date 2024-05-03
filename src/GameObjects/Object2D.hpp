#pragma once
#include "GameObject.hpp"
#include "../AsteroidMath/Vector2.hpp"

/**
 * @brief Base class for all 2D game objects.
 *
 */
class Object2D : public GameObject, public sf::Transformable
{
public:
    /**
     * @brief Draws to the render target using a base transform.
     * This is used for the "root" of a game object hierarchy, and in general should only be called on a single Object2D per scene.
     *
     * @param target Render target to draw to, i.e. a window or a texture.
     */
    virtual void draw(sf::RenderTarget &target) const override;
    /**
     * @brief Called by the parent Object2D (soon to be changed when Y-sorting is introduced).
     * While this can be overridden, it is best to specify render behavior in `onDraw()` (this may change later).
     *
     * @param target Render target to draw to, i.e. a window or a texture.
     * @param parentTransform The transform of the parent Object2D, used to calculate the final transform required for rendering.
     */
    virtual void draw(sf::RenderTarget &target, const sf::Transform &parentTransform) const;
    /**
     * @brief The core update loop, called by the game render loop and passed down to subsequent children of the Object2Ds.
     *
     * @param delta Time in seconds since the last frame. Multiply this with time-sensitive calculations for framerate-independent results.
     */
    virtual void update(float delta) override;

protected:
    std::vector<Object2D *> children;

private:
    /**
     * @brief Object-defined drawing behavior.
     *
     * @param target Render target to draw to, i.e. a window or a texture.
     * @param transform The resulting transform of this object's transform combined with the parent's transform, needed for accurate drawing results.  
     */
    virtual void onDraw(sf::RenderTarget&, const sf::Transform &) const {};
};