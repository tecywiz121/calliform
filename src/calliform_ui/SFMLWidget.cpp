#include "SFMLWidget.hpp"
#include <iostream>
#include <exception>

#if !(defined (GDK_WINDOWING_WIN32) || defined (GDK_WINDOWING_X11))
#   error "No supported GDK backends enabled (only X11 and WIN32 are supported)"
#endif

#ifdef GDK_WINDOWING_WIN32
#   include <gdk/gdkwin32.h>
#endif

#ifdef GDK_WINDOWING_X11
#   include <gdk/gdkx.h>
#endif

SFMLWidget::SFMLWidget(sf::VideoMode mode, int size_request)
{
    if (size_request <= 0)
    {
        size_request = std::max<int>(1, std::min<int>(mode.width,
                                                      mode.height) / 2);
    }

    set_size_request(size_request, size_request);

    // Makes this behave like an interal object rather than a parent window.
    set_has_window(false);
}

SFMLWidget::~SFMLWidget()
{
}

void SFMLWidget::on_size_allocate(Gtk::Allocation& allocation)
{
    std::cout << "on_size_allocated" << std::endl;
    // Do something with the space that we have actually been given: (We will
    // not be given heights or widths less than we have requested, though we
    // might get more.)

    this->set_allocation(allocation);

    if(m_refGdkWindow)
    {
        m_refGdkWindow->move_resize(allocation.get_x(),
                                    allocation.get_y(),
                                    allocation.get_width(),
                                    allocation.get_height() );
        renderWindow.setSize(sf::Vector2u(allocation.get_width(),
                                          allocation.get_height()));
    }
}

void SFMLWidget::on_realize()
{
    std::cout << "on_realize" << std::endl;
    Gtk::Widget::on_realize();

    if(!m_refGdkWindow)
    {
        //Create the GdkWindow:
        GdkWindowAttr attributes;
        memset(&attributes, 0, sizeof(attributes));

        Gtk::Allocation allocation = get_allocation();

        //Set initial position and size of the Gdk::Window:
        attributes.x = allocation.get_x();
        attributes.y = allocation.get_y();
        attributes.width = allocation.get_width();
        attributes.height = allocation.get_height();

        attributes.event_mask = get_events () | Gdk::EXPOSURE_MASK | Gdk::BUTTON_PRESS_MASK;
        attributes.window_type = GDK_WINDOW_CHILD;
        attributes.wclass = GDK_INPUT_OUTPUT;


        m_refGdkWindow = Gdk::Window::create(get_window(), &attributes,
                GDK_WA_X | GDK_WA_Y);
        set_has_window(true);
        set_window(m_refGdkWindow);

        // transparent background
#if GTK_VERSION_GE(3, 0)
        this->unset_background_color();
#else
        this->get_window()->set_back_pixmap(Glib::RefPtr<Gdk::Pixmap>());
#endif

        this->set_double_buffered(false);

        //make the widget receive expose events
        m_refGdkWindow->set_user_data(gobj());

        Glib::RefPtr<Gdk::Display> display = m_refGdkWindow->get_display();
        GdkDisplay* cdisplay = display->gobj();

#ifdef GDK_WINDOWING_WIN32
        if (GDK_IS_WIN32_DISPLAY (cdisplay))
        {
            renderWindow.create(GDK_WINDOW_HANDLE(m_refGdkWindow->gobj()));
        }
        else
#endif
#ifdef GDK_WINDOWING_X11
        if (GDK_IS_X11_DISPLAY (cdisplay))
        {
            renderWindow.create(GDK_WINDOW_XID(m_refGdkWindow->gobj()));
        }
        else
#endif
        throw std::exception();
    }
}

void SFMLWidget::on_unrealize()
{
    std::cout << "on_unrealize" << std::endl;
    m_refGdkWindow.clear();

    // Call base class:
    Gtk::Widget::on_unrealize();
}

void SFMLWidget::display()
{
    std::cout << "display" << std::endl;
    if(m_refGdkWindow)
    {
        renderWindow.display();
    }
}

void SFMLWidget::invalidate()
{
    std::cout << "invalidate" << std::endl;
    if(m_refGdkWindow)
    {
        m_refGdkWindow->invalidate(true);
    }
}
