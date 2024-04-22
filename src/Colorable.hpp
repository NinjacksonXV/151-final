#include "ColorPalette.hpp"

/**
 * @brief Required by any object that would be changed by the color palette.
 *
 */
class Colorable
{
public:
    virtual void setColorPalette(ColorPalette colorPalette) = 0;
};