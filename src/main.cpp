#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include "GameObjects/Player.hpp"
#include "GameObjects/TestObject.hpp"
#include "Icon.cpp"
#include "GameObjects/Asteroid.hpp"
#include "GUI.hpp"
#define M_TAU (M_PI * 2.0f)

sf::RenderTarget const *windowAccessor; // Make this a public static accessor of Game class later
sf::View const *gameViewAccessor;

const std::string colorShaderStr =
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
// "gl_FragColor = vec4(0.0, 1.0, 0.0, 0.0);"
"}"
;

// TO-DO: Move most of this logic to Game class
int main()
{
    auto window = sf::RenderWindow{{1920u, 1080u}, "Asteroids", sf::Style::Titlebar | sf::Style::Close}; // This is nice to avoid resizing issues
    window.setIcon(icon.width, icon.height, icon.pixel_data);
    window.setFramerateLimit(144);
    windowAccessor = &window;

    Player player;
    TestObject circle({10.0, 10.0});
    std::vector<sf::Vector2f> a = {
        {0.0f, 0.0f},
        {20.0f, 0.0f},
        {20.0f, 20.0f}};
    Asteroid asteroidTest(
        {{0.0f, 0.0f},
         {100.0f, 0.0f},
         {100.0f, 100.0f}},
        sf::Vector2f(100.0f, -100.0f));
    asteroidTest.Shape::setPosition(0.f, 0.f);
    std::vector<GameObject *> gameObjects = {&player, &circle, &asteroidTest};

    sf::View gameView({0.f, 0.f}, sf::Vector2f(window.getSize().y, window.getSize().y));
    gameView.setViewport(sf::FloatRect((static_cast<float>(window.getSize().x) - static_cast<float>(window.getSize().y)) / 2.f / static_cast<float>(window.getSize().x), 0.f,
                                       (static_cast<float>(window.getSize().y)) / (static_cast<float>(window.getSize().x)),
                                       1.0f));

    gameViewAccessor = &gameView;
    sf::Clock clock;

    sf::Shader colorShader;
    colorShader.loadFromMemory(colorShaderStr, sf::Shader::Fragment);
    colorShader.setUniform("texture", sf::Shader::CurrentTexture);
    // colorShader.setUniform("primary", sf::Glsl::Vec4(sf::Color::Black)); 
    // colorShader.setUniform("secondary", sf::Glsl::Vec4(sf::Color::White));

    colorShader.setUniform("primary", sf::Glsl::Vec4(sf::Color::Black)); 
    colorShader.setUniform("secondary", sf::Glsl::Vec4(sf::Color::White));


    sf::Texture door1Texture;
    door1Texture.loadFromFile("../../asset-source/door1.png");
    sf::Sprite door1_l(door1Texture), door1_r(door1Texture);
    door1_l.setScale(gameView.getSize().x / door1Texture.getSize().x, gameView.getSize().y / door1Texture.getSize().y);
    door1_r.setScale(gameView.getSize().x / door1Texture.getSize().x * -1.f, gameView.getSize().y / door1Texture.getSize().y);

    door1_l.setOrigin(door1Texture.getSize().x, 0.0f);
    door1_r.setOrigin(door1Texture.getSize().x, 0.0f);

    // door1_l.setPosition((window.getSize().x - gameView.getSize().x) / 2.0f, 0.0);
    door1_l.setPosition(window.getSize().x / 2.0f - gameView.getSize().x / 2.0f, 0.0f);
    door1_r.setPosition((window.getSize().x - gameView.getSize().x) / 2.0f + gameView.getSize().x, 0.0f);



    for (GameObject *gameObject : gameObjects)
    {
        gameObject->init();
    }

    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::Resized)
            {
                gameView.setSize(event.size.width, event.size.height); // Currently unused since resizing is disabled. Wouldn't work in current state.
            }
        }

        window.clear();
        window.setView(gameView);
        for (GameObject *gameObject : gameObjects)
        {
            gameObject->update(elapsed.asSeconds());
            gameObject->draw(window);
        }
        door1_r.move(elapsed.asSeconds() * 3.f, 0.0f);
        window.setView(window.getDefaultView());
        window.draw(door1_l, &colorShader);
        window.draw(door1_r, &colorShader);
        // std::cout << asteroidTest.getGlobalBounds();

        // if (player.getGlobalBounds().intersects(asteroidTest.getGlobalBounds()))
        // {
        //     std::cout << "AABB collision\n";
        // }
        window.display();
    }
}

const std::string shapeFragShader =
    "#version 130\n"
    "uniform float radius;"
    "uniform vec2 u_resolution;"
    "uniform vec2 position;"
    "uniform sampler2D image;"
    ""
    "vec4 blur13(sampler2D image, vec2 uv, vec2 resolution, vec2 direction) {"
    "   vec4 color = vec4(0.0);"
    "   vec2 off1 = vec2(1.411764705882353) * direction;"
    "   vec2 off2 = vec2(3.2941176470588234) * direction;"
    "   vec2 off3 = vec2(5.176470588235294) * direction;"
    "   color += texture2D(image, uv) * 0.1964825501511404;"
    "   color += texture2D(image, uv + (off1 / resolution)) * 0.2969069646728344;"
    "   color += texture2D(image, uv - (off1 / resolution)) * 0.2969069646728344;"
    "   color += texture2D(image, uv + (off2 / resolution)) * 0.09447039785044732;"
    "   color += texture2D(image, uv - (off2 / resolution)) * 0.09447039785044732;"
    "   color += texture2D(image, uv + (off3 / resolution)) * 0.010381362401148057;"
    "   color += texture2D(image, uv - (off3 / resolution)) * 0.010381362401148057;"
    "   return color;"
    "}"
    ""
    "void main() {"
    "vec2 uv = vec2(gl_FragCoord.xy / u_resolution);"
    "gl_FragColor = blur13(image, uv, u_resolution, vec2(.5,.2));"
    "}";

// int main()
// {
//     sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Shader Glow Effect");

//     // sf::CircleShape circle(100.0f);
//     // circle.setPosition(300, 200);
//     // circle.setFillColor(sf::Color::White);

//     sf::RectangleShape stars(static_cast<sf::Vector2f>(window.getSize()));
//     stars.setFillColor(sf::Color::Black);

//     sf::Shader shapeShader;

//     sf::ConvexShape shape(4);
//     shape.setPoint(0, {30, -10});
//     shape.setPoint(1, {0, 0});
//     shape.setPoint(2, {-30, -10});
//     shape.setPoint(3, {0, 40});
//     shape.setFillColor(sf::Color::Black);
//     shape.setOutlineColor(sf::Color::White);
//     shape.setOutlineThickness(4.0f);
//     shape.setPosition(50, 50);
//     sf::RenderTexture rTexture;
//     rTexture.create(100, 100);
//     rTexture.draw(shape);
//     shapeShader.loadFromMemory(shapeFragShader, sf::Shader::Fragment);
//     shapeShader.setUniform("u_resolution", sf::Vector2f(window.getSize().x, window.getSize().y));
//     shapeShader.setUniform("image", rTexture.getTexture());
//     rTexture.getTexture().copyToImage().saveToFile("ship.png");
//     return 0;
//     sf::Sprite sprite(rTexture.getTexture());

//     sf::Shader shader;
//     sf::Shader starShader;

//     sprite.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }

//         window.clear();
//         window.draw(stars);
//         window.draw(sprite, &shapeShader);
//         window.display();
//     }

//     return 0;
// }