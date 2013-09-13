#include <cassert>
#include <iostream>
#include <glibmm/refptr.h>
#include <gtkmm/window.h>
#include <gtkmm/builder.h>
#include "calliform.hpp"
#include "SFMLWidget.hpp"

int main(int argc, char* argv[])
{
    // Make sure we can call functions from libcalliform
    assert(test_this(5, 5) == 25);

    Glib::RefPtr<Gtk::Application> app =
        Gtk::Application::create(argc, argv,
            "org.calliform.main");

    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("test.glade");

    Gtk::Window* window = 0;
    builder->get_widget("MainWindow", window);

    SFMLWidget* area = 0;
    builder->get_widget_derived("DrawingArea", area);

    if (area)
    {
        std::cout << "Found Area" << std::endl;
    }
    else
    {
        std::cout << "No Area" << std::endl;
    }

    return app->run(*window);
}
