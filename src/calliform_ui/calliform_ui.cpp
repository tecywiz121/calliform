#include <cassert>
#include <gtkmm.h>
#include "calliform.hpp"

int main(int argc, char* argv[])
{
    assert(test_this(5, 5) == 25);

    Glib::RefPtr<Gtk::Application> app =
        Gtk::Application::create(argc, argv,
            "org.calliform.main");

    Gtk::Window window;
    window.set_default_size(200, 200);

    return app->run(window);
}
