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
#include "ColorShader.hpp"

enum class GameState
{
    Menu = 1,
    Paused = 2,
    NewRound = 4,
    Playing = 8,
    GameOver = 16
};

unsigned int lives = 3;

bool isFullScreen;

std::list<Colorable *> Colorable::colorables;

sf::RenderTarget const *windowAccessor; // Make this a public static accessor of Game class later
sf::View const *gameViewAccessor;
std::list<Bullet *> *bulletAccessor;
std::list<Asteroid *> *asteroidAccessor;
std::list<GameObject *> *gameObjectAccessor;

int asteroidLimit = 15;
float asteroidSpawnCooldown = 5.f;

// TO-DO: Move most of this logic to Game class
int main()
{
    GameState gameState = GameState::Playing;
    Game::setColorPalette(ColorPalette::basic);
    isFullScreen = false;
    auto window = sf::RenderWindow{{1920u, 1080u}, "Asteroids", sf::Style::Titlebar | sf::Style::Close}; // This is nice to avoid resizing issues

    window.setIcon(icon.width, icon.height, icon.pixel_data);
    window.setFramerateLimit(144);
    window.setVerticalSyncEnabled(true);
    windowAccessor = &window;

    Player player;
    TempStars stars;
    std::list<GameObject *> gameObjects = {&stars};
    std::list<Bullet *> bullets;
    std::list<Asteroid *> asteroids;
    bulletAccessor = &bullets;
    asteroidAccessor = &asteroids;
    gameObjectAccessor = &gameObjects;

    ColorShader colorShader;

    sf::View gameView({0.f, 0.f}, sf::Vector2f(window.getSize().y, window.getSize().y));
    gameView.setViewport(sf::FloatRect((static_cast<float>(window.getSize().x) - static_cast<float>(window.getSize().y)) / 2.f / static_cast<float>(window.getSize().x), 0.f,
                                       (static_cast<float>(window.getSize().y)) / (static_cast<float>(window.getSize().x)),
                                       1.0f));

    gameViewAccessor = &gameView;
    sf::Clock clock;

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
    player.init();
    new Asteroid(4);

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
                gameView.setSize(event.size.width, event.size.height); // Currently unused since resizing is disabled. Wouldn't work in current state, since the gameView is set with some calculations.
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            window.create({1920, 1080}, "Asteroids", (isFullScreen ? sf::Style::Titlebar | sf::Style::Close : sf::Style::Fullscreen));
            isFullScreen = true;
            window.setVerticalSyncEnabled(true);
            window.setFramerateLimit(144);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
        {
            Game::setColorPalette(ColorPalette::bumblebit);
            Colorable::updateColorPalette(Game::getColorPalette());
        }

        window.clear();

        switch (gameState)
        {
        case GameState::Menu:
        {
            break;
        }
        case GameState::NewRound:
        {
            break;
        }
        case GameState::Playing:
        {
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
            player.update(elapsed.asSeconds());
            stars.updatePosition(player.getVelocity() * elapsed.asSeconds());
            for (Asteroid *asteroid : asteroids)
            {
                asteroid->update(elapsed.asSeconds());
                asteroid->draw(window);
                if (asteroid->getGlobalBounds().intersects(player.getGlobalBounds()))
                {
                    Collision::checkForCollision(&player, asteroid);
                }
            }

            for (Bullet *bullet : bullets)
            {
                bullet->update(elapsed.asSeconds());
                bullet->Object2D::draw(window);
                for (Asteroid *asteroid : asteroids)
                {
                    if (asteroid->getGlobalBounds().contains(bullet->Object2D::getPosition()))
                    {
                        Collision::checkForCollision(bullet, asteroid);
                    }
                }
            }
            bullets.remove_if([](Bullet *bullet)
                              { return bullet->queueDelete; });
            player.draw(window);

            // if (asteroids.size() < asteroidLimit && asteroidSpawnCooldown < 0.f)
            // {
            //     new Asteroid(4);
            //     asteroidSpawnCooldown = 5.f;
            // }
            // asteroidSpawnCooldown -= elapsed.asSeconds();
        }
        case GameState::Paused:
            break;
        case GameState::GameOver:
            break;
        }

        window.setView(window.getDefaultView());
        window.draw(door1_l, &colorShader);
        window.draw(door1_r, &colorShader);
        window.display();
    }
}