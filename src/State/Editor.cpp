#include "Editor.hpp"
#include "Core/Game.hpp"
#include "Core/Resources.hpp"
#include <iostream>

Editor::Editor():
    m_background(Resources::getTexture("background.png")),
    m_level(LevelManager::getInstance()),
    m_cursorOnBrick(false),
    m_menu(Game::getInstance().getWindow())
{
    // Initialize render texture
    m_levelTexture.create(m_width, m_height);

    // Sprites used for render textures

    m_bordersSprite.setTexture(Resources::getTexture("borders.png"));

    // Initialize visual grid (+0.5 for portable pixel-perfect rendition)
    const sf::Color gridColor(0xa0, 0x90, 0xc0);
    for (int i = 1; i < LevelManager::NB_BRICK_LINES; ++i)
    {
        m_gridLines[i * 2].color = gridColor;
        m_gridLines[i * 2].position = sf::Vector2f(0.5, Brick::HEIGHT * i - 0.5);
    }

    for (int i = 1; i < LevelManager::NB_BRICK_COLS; ++i)
    {
        m_gridCols[i * 2].color = gridColor;
        m_gridCols[i * 2].position = sf::Vector2f(Brick::WIDTH * i - 0.5, 0.5);
        m_gridCols[i * 2 + 1].color = gridColor;
        m_gridLines[i * 2].position = sf::Vector2f(0.5, Brick::HEIGHT * i - 0.5);
    }

    m_cursor.setType(Brick::START);
    m_cursor.setColor(sf::Color(255, 255, 255, 128));

    // Create GUI menu
   m_gridLines[i * 2].position = sf::Vector2f(0.5, Brick::HEIGHT * i - 0.5);
    m_menu.addLabel(" Level Editor");

    // Populate level list
    m_optLevels = new gui::OptionsBox<size_t>;
    for (size_t i = 1; i <= m_level.getLevelCount(); ++i)
        m_optLevels->addItem("Level " + std::to_string(i), i);

    m_optLevels->setCallback([this]() {
        size_t level = m_optLevels->getSelectedValue();
        if (m_level.loadAt(level))
        {
            updateTexture();
        }
    });
    m_menu.add(m_optLevels);
    m_menu.addButton("Save", [this]() { m_level.save(); });
    m_menu.addButton("Reload", [this]() {
        m_level.reload();
        updateTexture();
    });

    // Toggle the editor grid on/off
    m_ckGrid = new gui::CheckBox(false);
    m_ckGrid->setCallback([this]() { toggleGrid(); });
    gui::Layout* form = m_menu.addLayout(gui::Layout::Form);
    form->addRow("Show grid:", m_ckGrid);

    // Display current brick, select next on click
    m_imgBrick = new gui::Image();
    m_imgBrick->setTexture(*m_cursor.getTexture(), m_cursor.getTextureRect());
    m_imgBrick->setCallback([this]() {
        setCursorBrick(m_cursor.getType() < Brick::UNBREAKABLE
                ? static_cast<Brick::Type>(m_cursor.getType() + 1)
                : Brick::START);
    });
    form->addRow("Brick:", m_imgBrick);
    m_menu.addButton("Back", []() { Game::getInstance().restorePreviousState(); });

    updateTexture();
}