#ifndef GUI_ARROW_HPP
#define GUI_ARROW_HPP

#include <SFML/Graphics.hpp>

namespace gui
{


class Arrow: public sf::Drawable
{
public:
    enum Direction { Left, Right, Top, Bottom };

    Arrow();
    Arrow(float size, Direction direction);

    void build(float size, Direction direction);

    void move(float dx, float dy);
    void setPosition(float x, float y);

    sf::Vector2f getSize() const;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


    sf::Vertex m_triangle[3];
    Direction m_direction;
};

}

#endif // GUI_ARROW_HPP
