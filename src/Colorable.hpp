#pragma once
#include <list>
// #include "Game.hpp"
#include "ColorPalette.hpp"

/**
 * @brief Required by any object that would be changed by the color palette.
 *
 */
class Colorable
{
private:
    static std::list<Colorable *> colorables;

public:
    Colorable()
    {
        Colorable::colorables.push_back(this);
    }
    ~Colorable()
    {
        colorables.remove(this);
    }
    static void updateColorPalette(const ColorPalette &colorPalette)
    {
        for (Colorable *colorable : colorables)
        {
            colorable->setColorPalette(colorPalette);
        }
    }
    virtual void setColorPalette(const ColorPalette &colorPalette) = 0;
};