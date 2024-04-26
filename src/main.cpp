#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define _USE_MATH_DEFINES
#include <math.h>
#define M_TAU (M_PI * 2.0f)

#include "GameObjects/Player.hpp"
#include "GameObjects/TestObject.hpp"
#include "Icon.cpp"
#include "GameObjects/Asteroid.hpp"
#include "Collision.hpp"

// #include "MusicHandler.hpp"

sf::RenderTarget const *windowAccessor; // Make this a public static accessor of Game class later
sf::View const *gameViewAccessor;
std::list<Bullet *> *bulletAccessor;
std::list<Asteroid *> *asteroidAccessor;
std::list<GameObject *> *gameObjectAccessor;

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
    "}";

// TO-DO: Move most of this logic to Game class
int main()
{
    Game::setColorPalette(ColorPalette::basic);
    auto window = sf::RenderWindow{{1920u, 1080u}, "Asteroids", sf::Style::Titlebar | sf::Style::Close}; // This is nice to avoid resizing issues

    window.setIcon(icon.width, icon.height, icon.pixel_data);
    window.setFramerateLimit(144);
    window.setVerticalSyncEnabled(true);
    windowAccessor = &window;

    Player player;
    TempStars stars;
    // Asteroid asteroid({{0.f, 0.f},{25.f, 0.f},{54.f, 30.f},{36.f, 45.f},{-10.f, 70.f},{-20.f, 35.f},{-25.f, 10.f}}, {0.f, 0.f});
    std::list<GameObject *> gameObjects = {&stars, &player};
    std::list<Bullet *> bullets;
    std::list<Asteroid *> asteroids;
    bulletAccessor = &bullets;
    asteroidAccessor = &asteroids;
    gameObjectAccessor = &gameObjects;
    Asteroid asteroid(4);

    sf::View gameView({0.f, 0.f}, sf::Vector2f(window.getSize().y, window.getSize().y));
    gameView.setViewport(sf::FloatRect((static_cast<float>(window.getSize().x) - static_cast<float>(window.getSize().y)) / 2.f / static_cast<float>(window.getSize().x), 0.f,
                                       (static_cast<float>(window.getSize().y)) / (static_cast<float>(window.getSize().x)),
                                       1.0f));

    gameViewAccessor = &gameView;
    sf::Clock clock;

    sf::Shader colorShader;
    colorShader.loadFromMemory(colorShaderStr, sf::Shader::Fragment);
    colorShader.setUniform("texture", sf::Shader::CurrentTexture);

    colorShader.setUniform("primary", sf::Glsl::Vec4(Game::getColorPalette().primary));
    colorShader.setUniform("secondary", sf::Glsl::Vec4(Game::getColorPalette().secondary));
    colorShader.setUniform("tertiary", sf::Glsl::Vec4(Game::getColorPalette().tertiary));

    sf::Texture door1Texture;
    door1Texture.loadFromFile("../../asset-source/door1.png");
    door1Texture.generateMipmap();
    sf::Sprite door1_l(door1Texture), door1_r(door1Texture);
    door1_l.setScale(gameView.getSize().x / door1Texture.getSize().x, gameView.getSize().y / door1Texture.getSize().y);
    door1_r.setScale(gameView.getSize().x / door1Texture.getSize().x * -1.f, gameView.getSize().y / door1Texture.getSize().y);

    door1_l.setOrigin(door1Texture.getSize().x, 0.0f);
    door1_r.setOrigin(door1Texture.getSize().x, 0.0f);

    door1_l.setPosition(window.getSize().x / 2.0f - gameView.getSize().x / 2.0f, 0.0f);
    door1_r.setPosition((window.getSize().x - gameView.getSize().x) / 2.0f + gameView.getSize().x, 0.0f);

    sf::InputSoundFile musicFile;
    musicFile.openFromFile("../../asset-source/music/bass3.wav");
    sf::InputSoundFile musicFile2;
    musicFile2.openFromFile("../../asset-source/music/drums.wav");

    sf::Music test1;
    test1.openFromFile("../../asset-source/music/bass3.wav");
    sf::Music test2;
    test2.openFromFile("../../asset-source/music/drums.wav");

    test1.setLoop(true);
    test2.setLoop(true);

    // test1.play();

    sf::Sound soundTest;
    sf::SoundBuffer soundTestBuffer;
    soundTestBuffer.loadFromFile("../../asset-source/music/drums.wav");
    soundTest.setBuffer(soundTestBuffer);

    soundTest.setLoop(true);

    soundTest.play();

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

            if(useMenu)
            mainMenu.update(event, window);

            if(usePause)
            pauseMenu.update(event, window);
            score.update(event, window);

            if(mainMenu.isClicked(0))
            {
                useMenu = false;
                usePlaying = true;
            }

            if(usePlaying && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                usePause = true;
            }

        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            window.create({1920, 1080}, "Asteroids", sf::Style::Fullscreen);
            window.setFramerateLimit(144);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
        {
            Game::setColorPalette(ColorPalette::bumblebit);
            player.setColorPalette(Game::getColorPalette());
            colorShader.setUniform("primary", sf::Glsl::Vec4(Game::getColorPalette().primary));
            colorShader.setUniform("secondary", sf::Glsl::Vec4(Game::getColorPalette().secondary));
            colorShader.setUniform("tertiary", sf::Glsl::Vec4(Game::getColorPalette().tertiary));

            // musicHandler.queueUp(musicFile2);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            asteroid.Object2D::move({0.f, -10.f});

            // musicHandler.queueUp(musicFile2);
        }

        window.clear();
        window.setView(gameView);

        asteroids.remove_if([](Asteroid *asteroid)
                            { return asteroid->queueDelete; });

        gameObjects.remove_if([](GameObject *gameObject)
                              { return gameObject->queueDelete; });

        for (GameObject *gameObject : gameObjects)
        {
            gameObject->update(elapsed.asSeconds());
            gameObject->draw(window);
        }
        for (Asteroid *asteroid : asteroids)
        {
            asteroid->update(elapsed.asSeconds());
            asteroid->draw(window);
            if (asteroid->getGlobalBounds().intersects(player.getGlobalBounds()))
            {
                Collision::checkForCollision(&player, asteroid);
            }
        }
        stars.updatePosition(player.getVelocity());

        for (Bullet *bullet : bullets)
        {
            bullet->update(elapsed.asSeconds());
            bullet->Object2D::draw(window);
            for (Asteroid *asteroid : asteroids)
            {
                if (asteroid->getGlobalBounds().contains(bullet->Object2D::getPosition()))
                {
                    if (Collision::checkForCollision(bullet, asteroid))
                        break;
                }
            }
        }
        bullets.remove_if([](Bullet *bullet)
                          { return bullet->queueDelete; });

        window.setView(window.getDefaultView());
        window.draw(door1_l, &colorShader);
        window.draw(door1_r, &colorShader);
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