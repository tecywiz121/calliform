#include <cassert>
#include <iostream>
#include <gtkmm.h>
#include "calliform.hpp"
#include "SFMLWidget.hpp"
#include "Canvas.hpp"
#include "BrushesImage.hpp"
#include "BrushesProperty.hpp"

#if 0
class MovingCircle
{
public:
    // a reference to our SFMLWidget
    SFMLWidget& widget;

    cf::Brushes::Image brush;
    sf::Sprite sprite;

    // The radius of our circle
    float radius;

    MovingCircle(SFMLWidget& widget) : widget(widget)
    {
        // drawing a sprite
        // Load a texture from a file
        cf::Brushes::Value<unsigned int> d;
        d.set(32);
        brush.setProperty(cf::Brushes::Image::PROP_DIAMETER, d);

        cf::Brushes::Value<std::string> s;
        s.set("cat.png");
        brush.setProperty(cf::Brushes::Image::PROP_SOURCE, s);

        brush.prepare();

        // move the circoe to it's first position
        moveToStartPoint();

        // Let the animate method be called every 50ms
        // Note: MovingCircle::animate() doesn't return any value, but signal_timeout() expects
        //       a boolean value.
        //       Using sigc::bind_return(true, ...) we get a signal returning always true.
        Glib::signal_timeout().connect(sigc::bind_return(
                                          sigc::mem_fun(this, &MovingCircle::animate),
                                          true),
                                       50);

        // Makes our draw Method beeing drawn everytime the widget itself gets drawn.
        // Note: MovingCircle::draw() doesn't accept any parameter, but signal_draw() gives one.
        //       Using sigc::hide(...) we get a signal expecting one.
        widget.signal_draw().connect(sigc::bind_return(
                                     sigc::hide(
                                         sigc::mem_fun(this, &MovingCircle::draw)),
                                     true));
        // NOTE: in earlier gtkmm-versions (<3.0) instead of signal_draw, connext to signal_event_expose:
        // widget.signal_event_expose().connect(sigc::bind_return(
        //                                          sigc::hide(
        //                                              sigc::mem_fun(this, &MovingCircle::draw)),
        //                                          true));

        // Everytime the widget gets resized, we need to adjust the view.
        widget.signal_size_allocate().connect(sigc::hide(
                                                    sigc::mem_fun(this, &MovingCircle::resize_view)));

        widget.signal_button_press_event().connect(sigc::mem_fun(this, &MovingCircle::button_press));
    }

    bool button_press(GdkEventButton* event)
    {
        cf::Brushes::Value<unsigned int> diameter;
        brush.getProperty(cf::Brushes::Image::PROP_DIAMETER, diameter);
        float r = diameter.get() / 2.f;
        sprite.setPosition(event->x - r, event->y - r);
        return true;
    }

    void animate()
    {
        // Tell gtkmm that the SFML Widget wants to be redrawn
        widget.invalidate();
    }

    void draw()
    {
        // Draw the textured sprite
        widget.renderWindow.clear();

        //widget.renderWindow.draw(circle);
        brush.render(sprite);

        widget.renderWindow.draw(sprite);

        // Calls SFMLWidget::display, whitch checks wether the widget is realized
        // and if so, sf::RenderWindow::display gets called.
        widget.display();
    }

    void resize_view()
    {
        // Let the View fit the pixels of the window.
        sf::Vector2f lower_right(widget.renderWindow.getSize().x,
                                 widget.renderWindow.getSize().y);

        sf::View view(lower_right * 0.5f,
                      lower_right);
        widget.renderWindow.setView(view);
    }

    void moveToStartPoint()
    {
        cf::Brushes::Value<unsigned int> diameter;
        brush.getProperty(cf::Brushes::Image::PROP_DIAMETER, diameter);
        sprite.setPosition(-(float)diameter.get(), -(float)diameter.get());
    }
};
#endif

class GdkCanvas : public cf::Canvas
{
private:
    SFMLWidget& _Widget;

public:
    GdkCanvas(SFMLWidget& w)
        : Canvas(w.renderWindow, sf::Vector2u(100, 100)), _Widget(w)
    {

    }
    virtual void invalidate()
    {
        _Widget.invalidate();
    }
};

int main(int argc, char* argv[])
{
    Gtk::Main kit(argc, argv); //Initialize Gtk

    Gtk::Window window; //The GTK window will be our top level Window

    //Our RenderWindow will never be below  640x480 (unless we explicitly change it)
    //but it may be more then that
    SFMLWidget ourRenderWindow(sf::VideoMode(640, 480));

    GdkCanvas canvas(ourRenderWindow);

    #if 0
    MovingCircle moving_circle(ourRenderWindow);
    #endif

    // Doesn't draw the renderWindow but makes it so it will draw when we add it to the window
    ourRenderWindow.show();

    //VBox is a vertical box, we're going to pack our render window and a button in here
    Gtk::VBox ourVBox;

    Gtk::Button ourButton("Add Layer"); //Just a clickable button, it won't be doing anything
    ourButton.show();
    ourButton.signal_clicked().connect(sigc::bind(sigc::hide_return(sigc::mem_fun(&canvas, &cf::Canvas::emplaceLayer)), canvas.layers().end()));

    Gtk::Button brushes("List Brushes");
    brushes.show();
    brushes.signal_clicked().connect([&canvas]() {
        canvas.scanBrushes();

        for (int bid : canvas.brushes())
        {
            std::cout << canvas.brushName(bid) << std::endl;
        }
    });

    ourVBox.pack_start(ourRenderWindow); //Add ourRenderWindow to the top of the VBox

    //PACK_SHRINK makes the VBox only allocate enough space to show the button and nothing more
    ourVBox.pack_start(brushes, Gtk::PACK_SHRINK);
    ourVBox.pack_start(ourButton, Gtk::PACK_SHRINK);
    ourVBox.show();

    window.add(ourVBox); //Adds ourVBox to the window so it (and it's children) can be drawn

    Gtk::Main::run(window); //Draw the window
    return 0;
}
