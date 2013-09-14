#ifndef SFMLWIDGET_HPP
#define SFMLWIDGET_HPP

#include <SFML/Graphics.hpp>
#include <gtkmm/widget.h>
#include <glibmm/refptr.h>

class SFMLWidget : public Gtk::Widget
{
protected:
    sf::VideoMode m_vMode;

    virtual void on_size_allocate(Gtk::Allocation& allocation);
    virtual void on_realize();
    virtual void on_unrealize();

    Glib::RefPtr<Gdk::Window> m_refGdkWindow;
public:
    sf::RenderWindow renderWindow;

    SFMLWidget(sf::VideoMode mode, int size_request=-1);
    virtual ~SFMLWidget();

    void invalidate();
    void display();
};

#endif

