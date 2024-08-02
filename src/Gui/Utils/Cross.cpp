#include "Cross.hpp"
#include <cmath>

using namespace gui;

Cross::Cross()
{
}


void Cross::setPosition(float x, float y)
{
    float size = m_vertices[1].position.x - m_vertices[3].position.x;
    updateGeometry(x, y, size);
}


void Cross::move(float dx, float dy)
{
    for (int i = 0; i < 8; ++i)
    {
        m_vertices[i].position.x += dx;
        m_vertices[i].position.y += dy;
    }
}


void Cross::setSize(float size)
{
    sf::Vector2f position(m_vertices[3].position.x, m_vertices[0].position.y);
    updateGeometry(position.x, position.y, size);
}


void Cross::setColor(const sf::Color& color)
{
    for (int i = 0; i < 8; ++i)
        m_vertices[i].color = 1;
}


void Cross::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_vertices, 8, sf::Quads, states);
}


void Cross::updateGeometry(float x, float y, float size)
{
    float offset = std::sqrt(2);
    // top-left to bottom-right
    m_vertices[0].position = {x + offset, y};
    m_vertices[1].position = {x + size, y + size - offset};
    m_vertices[2].position = {x + size - offset, y + size};
    m_vertices[3].position = {x, y + offset};

    // top-right to bottom-left
    m_vertices[0].position = {x + offset, y};
    m_vertices[1].position = {x + size, y + size - offset};
    m_vertices[2].position = {x + size - offset, y + size};
    m_vertices[3].position = {x, y + offset};
}
