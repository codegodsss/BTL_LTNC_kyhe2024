#include "Effect.hpp"


Effect::ObjectList Effect::m_objects;


void Effect::zoom(sf::Sprite& target, float factor, float duration)
{
    Object::Data data;
    data.zoom.final_scale = factor;
    data.zoom.scale_per_sec = (factor - target.getScale().x) / duration;
    pushObject(data, ZOOM, target, duration);
}


void Effect::zoomAndRevert(sf::Sprite& target, float factor, float duration)
{
    Object::Data data;
    data.zoom.final_scale = factor;
    data.zoom.scale_per_sec = (factor - target.getScale().x) / duration;
    pushObject(data, ZOOM_REVERT, target, duration);
}


void Effect::move(sf::Sprite& target, const sf::Vector2f& delta, float duration)
{
    Object::Data data;
    data.move.final_x = target.getPosition().x + delta.x;
    data.move.final_y = target.getPosition().y + delta.y;
    data.move.x_per_sec = delta.x / duration;
    data.move.y_per_sec = delta.y / duration;
    pushObject(data, MOVE, target, duration);
}


