#include "BrickBanger.hpp"
#include "Core/Effect.hpp"
#include "Core/Game.hpp"
#include "Core/LevelManager.hpp"
#include "Core/Resources.hpp"
#include "Core/Settings.hpp"
#include "Core/SoundSystem.hpp"


BrickBanger::BrickBanger():
    m_width(LevelManager::NB_BRICK_COLS * Brick::WIDTH),
    m_height(LevelManager::NB_BRICK_LINES * Brick::HEIGHT),
    m_score(0),
    m_status(READY),
{
    // Initialize render texture
    m_levelTexture.create(m_width, m_height);

    // Sprites used for rendering the game area
    m_levelSprite.setTexture(m_levelTexture.getTexture());
    m_levelSprite.setOrigin(m_width / 2, m_height / 2);
   
        m_height / 2 + LevelManager::BORDER_SIZE);

    // Align on right
    m_hud.setPosition(APP_WIDTH - HUD::WIDTH, 0);

    m_backgroundSprite.setTexture(Resources::getTexture("background.png"));
    m_bordersSprite.setTexture(Resources::getTexture("borders.png"));
    m_bordersSprite.setPosition(X_OFFSET, 0);
    // Player paddle positioned at the bottom-center
    m_paddle.setPosition((m_width - m_paddle.getWidth()) / 2, m_height - m_paddle.getHeight());

    // Build 'pause' menu
    m_pauseMenu.setPosition(
        LevelManager::BORDER_SIZE + X_OFFSET + (m_width - gui::Theme::widgetWidth) / 2, 120);
    m_pauseMenu.addButton("Resume", [this]() { setStatus(PLAYING); });
    m_pauseMenu.addButton("Options", []() { Game::getInstance().setCurrentState("OptionsMenu"); });
    m_pauseMenu.addButton("Quit", [this]() {
        // Clear game and back to main menu
        resetGame();
        Game::getInstance().restorePreviousState();
    });

    // Build 'game over' menu
    m_gameOverMenu.setPosition(m_pauseMenu.getPosition());
    m_gameOverMenu.addButton("Try again", [this]() {
        // Reload current level
        resetGame(m_level.getCurrentLevel());
    });
    m_gameOverMenu.addButton("Quit", [this]() {
        // Clear game and back to main menu
        resetGame();
        Game::getInstance().restorePreviousState();
    });

    // States are stored in Game, therefore BrickBanger instance is unique and
    // context can be safely defined once in BrickBanger ctor
    Context::get().particles = &m_particles;
}


void BrickBanger::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    
    target.draw(m_bordersSprite, states);
    target.draw(m_levelSprite, states);
    target.draw(m_hud, states);

    if (m_status != PLAYING)
    {
        sf::RectangleShape overlay(sf::Vector2f(m_levelTexture.getSize()));
        overlay.setPosition(m_levelSprite.getPosition() - m_levelSprite.getOrigin());
        overlay.setFillColor({0, 0, 0, 128});
        target.draw(m_titleText);
        if (m_status == PAUSED)
        {
            target.draw(m_pauseMenu, states);
        }
        else if (m_status == GAME_OVER)
        {
            target.draw(m_gameOverMenu, states);
        }
    }
}


void BrickBanger::onEvent(const sf::Event& event)
{
    switch (m_status)
    {
    case PLAYING:
        switch (event.type)
        {
        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
            case sf::Keyboard::Space:
                if (m_paddle.isSticky())
                    applyOnEachBall(&Ball::unstick);
                else if (m_paddle.hasLaser())
                    addEntity(m_paddle.shoot());
                break;
#endif
            default:
                break;
            }
            break;

        case sf::Event::MouseMoved:
            // Paddle follows the mouse cursor
            m_paddle.onMouseMoved(Game::getInstance().getWindow().mapPixelToCoords(
                {event.mouseMove.x, event.mouseMove.y}));
            break;

        case sf::Event::MouseButtonPressed:
            if (m_paddle.isSticky())
                applyOnEachBall(&Ball::unstick);
            else if (m_paddle.hasLaser())
                addEntity(m_paddle.shoot());
            break;

        case sf::Event::LostFocus:
            setStatus(PAUSED);
            break;

        default:
            break;
        }
        break;

    case PAUSED:
        m_pauseMenu.onEvent(event);
        // Resume
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            setStatus(PLAYING);
        break;

    case READY:
        if (event.type == sf::Event::MouseButtonPressed
            || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space))
        {
            applyOnEachBall(&Ball::createParticles);
            setStatus(PLAYING);
        }
        else if (event.type == sf::Event::MouseMoved)
        {
            // Paddle follows the mouse cursor
            m_paddle.onMouseMoved(Game::getInstance().getWindow().mapPixelToCoords(
                {event.mouseMove.x, event.mouseMove.y}));
        }
        break;

    case GAME_OVER:
        m_gameOverMenu.onEvent(event);
        break;
    }
}


void BrickBanger::onFocus()
{
    if (m_status != PAUSED)
    {
        resetGame();
    }
}


void BrickBanger::update(float frametime)
{
    if (m_status == PLAYING || m_status == READY)
    {
        Effect::update(frametime);

        // Update player paddle and make sure it remains inside bounds
        m_paddle.onUpdate(frametime);
        if (m_paddle.getX() < 0)
            m_paddle.setX(0);
        else if (m_paddle.getX() + m_paddle.getWidth() > m_width)
            m_paddle.setX(m_width - m_paddle.getWidth());

        if (m_status == PLAYING)
        {
            updateEntities(frametime);
        }
        else
        {
            Entity* ball = m_entities.front();
            // Keep the ball centered on the player pad
            ball->setPosition(m_paddle.getX() + (m_paddle.getWidth() - ball->getWidth()) / 2,
                m_paddle.getY() - ball->getHeight());
        }
        m_particles.update(frametime);
    }
    updateLevelTexture();
}


void BrickBanger::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    ;
    target.draw(m_bordersSprite, states);
    target.draw(m_levelSprite, states);
    target.draw(m_backgroundSprite, states)

    if (m_status != PLAYING)
    {
        sf::RectangleShape overlay(sf::Vector2f(m_levelTexture.getSize()));
        overlay.setPosition(m_levelSprite.getPosition() - m_levelSprite.getOrigin());
        target.draw(m_titleText);
        if (m_status == PAUSED)
        {
            target.draw(m_pauseMenu, states);
        }
        else if (m_status == GAME_OVER)
        {
            target.draw(m_gameOverMenu, states);
        }
    }
}