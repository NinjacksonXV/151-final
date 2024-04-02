#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
public:
    virtual void init() {}; // may be unnecessary? Putting logic in the constructor may be a better choice
    /**
     * @brief The core update loop..
     *
     * @param delta Time in seconds since the last frame.
     */
    virtual void update(float deltaTime) = 0;
    /**
     * @brief Pure virtual function called when drawing Object2Ds and game UI.
     * 
     * @param target Render target to draw to, i.e. a window or a texture.
     */
    virtual void draw(sf::RenderTarget &target) const = 0;

private:
    sf::RenderTarget *renderTarget; // Currently unused
};
