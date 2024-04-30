#include <sstream>

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
#include "AsteroidText.hpp"
#include "GameObjects/GUI/MenuButton.hpp"

enum class GameState
{
    Menu,
    Paused,
    NewRound,
    Playing,
    GameOver
};

unsigned int lives = 3;

bool isFullScreen;

std::list<Colorable *> Colorable::colorables;

sf::RenderTarget const *windowAccessor; // Make this a public static accessor of Game class later
sf::View const *gameViewAccessor;
std::list<Bullet *> *bulletAccessor;
std::list<Asteroid *> *asteroidAccessor;
std::list<GameObject *> *gameObjectAccessor;

float asteroid3SpawnCooldown = 5.f;
float asteroid4SpawnCooldown = 6.f;

// TO-DO: Move most of this logic to Game class
int main()
{
    std::vector<ColorPalette> palettes = {ColorPalette::basic,
                                          ColorPalette::bumblebit,
                                          ColorPalette::coldlight,
                                          ColorPalette::candy,
                                          ColorPalette::rust,
                                          ColorPalette::mushroom};
    GameState gameState = GameState::Menu;
    Asteroid::points = 0;
    size_t colorPaletteIterator = 0;
    bool paletteCycleLock = false;
    Game::setColorPalette(palettes[colorPaletteIterator]);
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

    sf::Font primary;
    primary.loadFromFile("../../asset-source/HyperspaceBold-GM0g.ttf");
    AsteroidText title, score, hp, instructions, paused, gameover;
    title.setFont(primary);
    score.setFont(primary);
    hp.setFont(primary);
    instructions.setFont(primary);
    paused.setFont(primary);
    gameover.setFont(primary);

    title.setString("Asteroids");
    title.setCharacterSize(100);
    title.setOrigin(title.getLocalBounds().width / 2.f, 0);
    title.setPosition(window.getSize().x / 2.f, 100);

    paused.setString("Paused");
    paused.setCharacterSize(100);
    paused.setOrigin(paused.getLocalBounds().width / 2.f, 0);
    paused.setPosition(window.getSize().x / 2.f, 100);

    hp.setString("HP: 0");
    hp.setCharacterSize(70);
    hp.setOrigin(hp.getLocalBounds().width, 0);
    hp.setPosition(window.getSize().x / 4.f - 200.f, 30.f);

    score.setString("SCORE: 00000");
    score.setCharacterSize(70);
    score.setOrigin(score.getLocalBounds().width / 2.f, 0);
    score.setPosition(((window.getSize().x) / 2.f), window.getSize().y - 300.f);

    instructions.setString(
        "    INSTRUCTIONS:\n\n"
        "     Accelerate\n"
        "          W           \n"
        "Left -- A / D -- Right\n"
        "       [Space]        \n"
        "        Shoot         \n"
        "\n"
        "       EXTRAS\n"
        "  P   -- Cycle colors");
    instructions.setLineSpacing(.9f);
    instructions.setCharacterSize(24);
    instructions.setOrigin(instructions.getLocalBounds().width, 0);
    instructions.setPosition(window.getSize().x - 24.f, 30.f);

    gameover.setString("Game\nOver");
    gameover.setCharacterSize(100);
    gameover.setOrigin(gameover.getLocalBounds().width / 2.f, 0);
    gameover.setPosition(window.getSize().x / 2.f, 100);

    MenuButton quit("Quit", primary);
    MenuButton play("Play", primary);
    MenuButton playAgain("Play Again", primary);

    play.setPosition(window.getSize().x / 2.f, window.getSize().y * (2.f / 3.f));
    std::cout << play.getPosition();
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
        window.clear();
        sf::Time elapsed = clock.restart();

        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.draw(door1_l, &colorShader);
        window.draw(door1_r, &colorShader);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            window.create({1920, 1080}, "Asteroids", (isFullScreen ? sf::Style::Titlebar | sf::Style::Close : sf::Style::Fullscreen));
            isFullScreen = true;
            window.setVerticalSyncEnabled(true);
            window.setFramerateLimit(144);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            if (paletteCycleLock == false)
            {
                colorPaletteIterator = (colorPaletteIterator == palettes.size() - 1 ? 0 : colorPaletteIterator + 1);
                Game::setColorPalette(palettes[colorPaletteIterator]);
                Colorable::updateColorPalette(Game::getColorPalette());
                paletteCycleLock = true;
            }
        }
        else
        {
            paletteCycleLock = false;
        }

        switch (gameState)
        {
        case GameState::Menu:
        {
            if (asteroids.empty())
            {
                new Asteroid(4);
                new Asteroid(3);
                new Asteroid(3);
                new Asteroid(2);
                new Asteroid(2);
                new Asteroid(1);
                new Asteroid(1);
            }
            window.setView(gameView);
            stars.draw(window);
            for (Asteroid *asteroid : asteroids)
            {
                asteroid->update(elapsed.asSeconds());
                asteroid->draw(window);
            }
            window.setView(window.getDefaultView());
            window.draw(instructions);
            window.draw(title);

            play.draw(window);
            // quit.draw(window);

            if (play.isPressed(window)) // Menu stuff later
            {
                for (Asteroid *asteroid : asteroids)
                {
                    delete asteroid;
                }
                score.setPosition(((window.getSize().x) / 2.f), window.getSize().y - 300.f);
                asteroids.clear();
                score.setString("SCORE: 00000");
                Asteroid::points = 0;
                player.init();
                gameState = GameState::NewRound;
                break;
            }
            break;
        }
        case GameState::NewRound:
        {
            window.setView(gameView);
            for (GameObject *gameObject : gameObjects)
            {
                gameObject->draw(window);
            }
            player.update(elapsed.asSeconds());
            player.draw(window);
            window.setView(window.getDefaultView());
            window.draw(instructions);
            if (player.state == Player::INITIALIZING)
            {
                gameState = GameState::Playing;
                break;
            }
            break;
        }
        case GameState::Playing:
        {
            if (player.state == Player::DEAD)
            {
                for (GameObject *gameObject : gameObjects)
                {
                    if (dynamic_cast<AccelerationLine *>(gameObject) != nullptr)
                    {
                        delete gameObject;
                    }
                }
                gameObjects.clear();
                gameObjects.push_back(&stars); // Stupid, but I can't clear out only AccelerationLines or it crashes :/
                for (Bullet *bullet : bullets)
                {
                    delete bullet;
                }
                for (Asteroid *asteroid : asteroids)
                {
                    delete asteroid;
                }
                asteroids.clear();
                bullets.clear();
                score.setPosition(((window.getSize().x) / 2.f), window.getSize().y - 700.f);
                gameState = GameState::GameOver;
                break;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                gameState = GameState::Paused;
                break;
            }
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

            int asteroidPool3 = 0;
            int asteroidPool4 = 0;
            for (Asteroid *asteroid : asteroids)
            {
                if (asteroid->getSize() == 3)
                    asteroidPool3++;
                if (asteroid->getSize() == 4)
                    asteroidPool4++;
            }

            if (asteroidPool3 < 3 && asteroid3SpawnCooldown <= 0.f)
            {
                new Asteroid(3);
                asteroid3SpawnCooldown = 5.f;
            }
            if (asteroidPool4 < 2 && asteroid4SpawnCooldown <= 0.f)
            {
                new Asteroid(4);
                asteroid4SpawnCooldown = 7.f;
            }
            asteroid3SpawnCooldown -= elapsed.asSeconds();
            asteroid4SpawnCooldown -= elapsed.asSeconds();

            window.setView(window.getDefaultView());

            std::stringstream scoreStream;
            std::string scoreString;
            scoreStream.width(5);
            scoreStream.fill('0');
            scoreStream << Asteroid::points;
            scoreStream >> scoreString;
            score.setString("SCORE: " + scoreString);
            window.draw(score);

            hp.setString("HP: " + std::to_string(player.getHP()));
            window.draw(hp);
            break;
        }
        case GameState::Paused:
        {
            window.setView(gameView);
            for (GameObject *gameObject : gameObjects)
            {
                gameObject->draw(window);
            }
            for (Bullet *bullet : bullets)
            {
                bullet->Object2D::draw(window);
            }
            for (Asteroid *asteroid : asteroids)
            {
                asteroid->Object2D::draw(window);
            }
            player.draw(window);

            window.setView(window.getDefaultView());
            window.draw(instructions);
            window.draw(paused);
            break;
        }
        case GameState::GameOver:
        {
            window.setView(gameView);
            stars.draw(window);
            window.setView(window.getDefaultView());
            window.draw(gameover);
            window.draw(score);
            break;
        }
        }
        window.setView(window.getDefaultView());
        window.display();
    }
}