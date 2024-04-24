#pragma once
#include "Game.hpp"
#include "ColorPalette.hpp"

/**
 * @brief Required by any object that would be changed by the color palette.
 *
 */
class Colorable
{
public:
    virtual void setColorPalette(const ColorPalette &colorPalette) = 0;
};