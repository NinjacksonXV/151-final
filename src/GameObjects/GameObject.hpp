#pragma once
#include <SFML/Graphics.hpp>

enum Flags
{
    Drawable = 0x01,
    

};

class GameObject
{
public:
    virtual ~GameObject() {};
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
    short int flags;  
    bool queueDelete = false;

private:
    sf::RenderTarget *renderTarget; // Currently unused
};
