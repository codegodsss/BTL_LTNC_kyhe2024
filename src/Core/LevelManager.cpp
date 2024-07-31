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
bool LevelManager::openFromFile(const std::string& filename)
{
    m_level_file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
    if (m_level_file)
    {
        // Number of levels = file size / size of one level
        m_level_file.seekg(0, std::ifstream::end);
        m_level_count = m_level_file.tellg() / LEVEL_BYTES;

        // Restore cursor position
        m_level_file.seekg(0);
        return true;
    }
    std::cerr << "error while opening level file " << filename << std::endl;
    return false;
}


int LevelManager::loadAt(size_t index)
{
    if (index > 0 && index <= m_level_count)
    {
        // -1 because stream cursor needs to be BEFORE the level
        m_current_level = index - 1;
        m_level_file.seekg(LEVEL_BYTES * m_current_level);
        return loadNext();
    }
    return false;
}


int LevelManager::loadPrevious()
{
    return loadAt(m_current_level - 1);
}


int LevelManager::reload()
{
    return loadAt(m_current_level);
}


int LevelManager::loadNext()
{
    m_brick_count = 0;

    if (m_level_file.eof())
        return 0;

    std::string line;
    for (int i = 0; i < NB_BRICK_LINES; ++i)
    {
        std::getline(m_level_file, line);
        if (m_level_file.eof())
        {
            return 0;
        }
        int length = line.size();
        for (int j = 0; j < NB_BRICK_COLS && j < length; ++j)
        {
            Brick& brick = m_bricks[i][j];
            // Set brick type
            Brick::Type type = static_cast<Brick::Type>(line[j]);
            brick.setType(type);
            if (type != Brick::NONE && type != Brick::UNBREAKABLE)
                ++m_brick_count;
            // Reset brick position and rotation
            brick.setPosition(j * Brick::WIDTH, i * Brick::HEIGHT);
            brick.setRotation(0);
            brick.setScale(1, 1);
        }
    }
    ++m_current_level;
#ifdef WALLBREAKER_DEBUG
    std::cout << "level " << m_current_level << "/" << m_level_count << " loaded, contains "
              << m_brick_count << " bricks" << std::endl;
#endif

    return m_brick_count;
}