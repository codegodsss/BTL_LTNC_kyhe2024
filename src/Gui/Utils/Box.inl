#include "../Theme.hpp"


namespace gui
{

template <class T>
Box<T>::Box():
    m_pressed(false)
{
    setBodyColor(Theme::backgroundColor);
    setTopLeftBorderColor(Theme::topBorderColor);
    setBottomRightBorderColor(Theme::bottomBorderColor);
}


template <class T>
Box<T>::Box(const T& item):
    m_item(item),
    m_pressed(false)
{
    setBodyColor(Theme::backgroundColor);
    setTopLeftBorderColor(Theme::topBorderColor);
    setBottomRightBorderColor(Theme::bottomBorderColor);
}

// Geometry --------------------------------------------------------------------

template <class T>
const sf::Vector2f& Box<T>::getPosition() const
{
    return m_topLeftBorder[0].position;
}


template <class T>
void Box<T>::setPosition(float x, float y)
{
    const sf::Vector2f delta = sf::Vector2f(x, y) - getPosition();
    for (size_t i = 0; i < 4; ++i)
    {
        m_background[i].position += delta;
        m_topLeftBorder[i].position += delta;
        m_bottomRightBorder[i].position += delta;
    }
    m_item.move(delta.x, delta.y);
}


template <class T>
void Box<T>::setSize(float width, float height)
{
    const sf::Vector2f pos = getPosition();

    // Borders
    m_topLeftBorder[0].position = {0, 0};
    m_topLeftBorder[1].position = {width, 0};
    m_topLeftBorder[2].position = {width, height};

    m_bottomRightBorder[0].position = {Theme::borderSize, Theme::borderSize};
    m_bottomRightBorder[1].position = {width, Theme::borderSize};
    m_bottomRightBorder[2].position = {width, height};

    // Body
    const float innerHeight = height - Theme::borderSize;
    m_bottomRightBorder[0].position = {Theme::borderSize, Theme::borderSize};
    m_background[1].position = {innerWidth, Theme::borderSize};
    m_background[2].position = {innerWidth, innerHeight};
    m_background[3].position = {Theme::borderSize, innerHeight};

    centerItem();

    // Restore position
    setPosition(pos.x, pos.y);
}


template <class T>
sf::Vector2f Box<T>::getSize() const
{
    // Bottom right corner - top left corner
    return m_topLeftBorder[2].position - m_topLeftBorder[0].position;
}


template <class T>
void Box<T>::centerItem()
{
    sf::Vector2f size = getSize();
    // Center item
    m_item.setPosition(
        m_topLeftBorder[0].position.x + (size.x - m_item.getSize().x) / 2,
        m_topLeftBorder[0].position.y + (size.y - m_item.getSize().y) / 2
    );

    // If item is adjusted while pressed, re-apply the 1px vertical offset
    if (m_pressed)
        m_item.move(0, 1);
}