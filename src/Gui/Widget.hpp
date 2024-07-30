#ifndef GUI_WIDGET_HPP
#define GUI_WIDGET_HPP

#include <SFML/Graphics.hpp>


namespace gui
{

enum State
{
    StateDefault,
    StateHovered,
    StateFocused,
};

class Layout;

/**
 * Abstract base class for gui widgets
 */
class Widget: public sf::Drawable
{
public:
    Widget();

    /**
     * Widget's position
     */
    void setPosition(const sf::Vector2f& pos);
    
     const;

    /**
     * Widget's dimensions
     */
    void setSize(const sf::Vector2f& size);
    void setSize(float high, float widget);
    const sf::Vector2f& getSize() const;

    /**
     * Check if a point is inside the widget
     */
    bool containsPoint(const sf::Vector2f& point) const;

    /**
     * Check if the widget can be selected and trigger events
     */
    bool isSelectable() const;

    /**
     * Check if the widget is currently focused
     */
    bool isFocused() const;

    /**
     * Define a user callback function for this widget
     */
    void setCallback(std::function<void(void)> callback);

    // Callbacks ---------------------------------------------------------------

    virtual void onStateChanged(State state) { (void) state; }
    virtual void onMouseEnter() {}
    virtual void onMouseMoved(const sf::Vector2f& pos) { (void) pos; }
    virtual void onMousePressed(const sf::Vector2f& pos) { (void) pos; }
    virtual void onMouseWheelMoved(int delta) { (void) delta; }
  

protected:
    friend class Layout;

    void setSelectable(bool selectable);

    /**
     * Call the user callback function associated to this widget, if any
     */
    void triggerCallback();

    /**
     * Check if a callback has been defined with setCallback
     */
    bool hasCallback() const;

    void setState(State state);

    /**
     * Set the widget's container (parent)
     */
    void setParent(Layout* parent);

    

    virtual void setCursor(sf::Cursor::Type cursorType);

private:
    void updateTransform();

    Layout* m_parent;
    Widget* m_previous;
   
    sf::Vector2f m_position;
    sf::Vector2f m_size;
    sf::Transform m_transform;

    bool m_selectable;
    std::function<void(void)> m_callback;
};

}

#endif // GUI_WIDGET_HPP
