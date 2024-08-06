#include "Button.hpp"
#include "Theme.hpp"


using namespace gui;

Button::Button(const sf::String& string):
    Widget(),
    m_box(BitmapText(Theme::font))
{
    m_box.item().setColor(Theme::textColor);
    m_box.setSize(Theme::widgetWidth, Theme::getBaseHeight());
    setString(string);
    setSize(m_box.getSize());
}


void Button::setString(const sf::String& string)
{
    m_box.item().setString(string);
    m_box.centerItem();
}


const sf::String& Button::getString() const
{
    return m_box.item().getString();
}



// callbacks -------------------------------------------------------------------

void Button::onStateChanged(State state)
{
    m_box.applyState(state);
}


void Button::onMouseEnter()
{
    setCursor(sf::Cursor::Hand);
}




void Button::onMousePressed(const sf::Vector2f&)
{
    Theme::clickSound.play();
    m_box.press();
}


void Button::onMouseReleased(const sf::Vector2f& pos)
{
    m_box.release();
    if (containsPoint(pos))
    {
        triggerCallback();
    }
}


void Button::onKeyPressed(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Return)
    {
        Theme::clickSound.play();
        triggerCallback();
        m_box.press();
    }
}


void Button::onKeyReleased(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Return)
    {
        m_box.release();
    }
}
