#include "Config.hpp"


Game& Game::getInstance()
{
    static Game self;
    return self;
}


Game::Game():
    m_fullscreen(false),
    m_running(true),
    m_view(sf::FloatRect(0, 0, APP_WIDTH, APP_HEIGHT)),
    m_currentState(nullptr)
{
}


Game::~Game()
{
}
