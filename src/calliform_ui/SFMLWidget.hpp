#ifndef SFMLWIDGET_HPP
#define SFMLWIDGET_HPP

#include <SFML/Graphics.hpp>
#include <gtkmm/drawingarea.h>
#include <glibmm/refptr.h>
#include <gtkmm/builder.h>

class SFMLWidget : public Gtk::DrawingArea
{
protected:
    sf::VideoMode m_vMode;

    virtual void on_size_allocate(Gtk::Allocation& allocation);
    virtual void on_realize();
    virtual void on_unrealize();
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);

    Glib::RefPtr<Gdk::Window> m_refGdkWindow;
public:
    sf::RenderWindow renderWindow;

    SFMLWidget(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
    SFMLWidget(sf::VideoMode mode, int size_request=-1);
    virtual ~SFMLWidget();

    void invalidate();
    void display();
};

#endif

