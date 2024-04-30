#include "Colorable.hpp"

class ColorShader : public sf::Shader, public Colorable
{
public:
    ColorShader()
    {
        loadFromMemory(
            "uniform sampler2D texture;"
            "uniform vec4 primary;"
            "uniform vec4 secondary;"
            "uniform vec4 tertiary;"
            ""
            "void main(){"
            "vec4 color = gl_Color * texture2D(texture, gl_TexCoord[0].st);"
            "vec3 color1 = vec3(color.r * primary.r, color.r * primary.g, color.r * primary.b);"
            "vec3 color2 = vec3(color.g * secondary.r, color.g * secondary.g, color.g * secondary.b);"
            "vec3 color3 = vec3(color.b * tertiary.r, color.b * tertiary.g, color.b * tertiary.b);"
            "gl_FragColor = vec4(color1 + color2 + color3, 1.0);"
            "}",
            sf::Shader::Fragment);
        setColorPalette(Game::getColorPalette());
    }
    void setColorPalette(const ColorPalette &colorPalette)
    {
        setUniform("primary", sf::Glsl::Vec4(colorPalette.primary));
        setUniform("secondary", sf::Glsl::Vec4(colorPalette.secondary));
        setUniform("tertiary", sf::Glsl::Vec4(colorPalette.tertiary));
    }
};