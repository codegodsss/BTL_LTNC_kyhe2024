#include "LevelManager.hpp"
#include <iostream>

/**
 * Number of bytes for each level in the levels file
 * NB_BRICK_COLS + 1 because additional '\n' character for each line
 */
#define LEVEL_BYTES ((NB_BRICK_COLS + 1) * NB_BRICK_LINES)


LevelManager& LevelManager::getInstance()
{
    static LevelManager self;
    return self;
}


LevelManager::LevelManager():
    m_current_level(0),
    m_level_count(0)
{
    // Initialize bricks position
    for (int i = 0; i < NB_BRICK_LINES; ++i)
        for (int j = 0; j < NB_BRICK_COLS; ++j)
            m_bricks[i][j].setPosition(j * Brick::WIDTH, i * Brick::HEIGHT);
}


LevelManager::~LevelManager()
{
    if (m_level_file.is_open())
        m_level_file.close();
}