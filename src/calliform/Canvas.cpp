#include <memory>
#include "Canvas.hpp"
#include "util.hpp"

namespace cf
{
    Canvas::Canvas(sf::RenderTarget& displayTarget, sf::Vector2u size)
        : _DisplayTarget(displayTarget), _Size(size)
    {

    }

    Layer& Canvas::PushLayer()
    {
        std::unique_ptr<Layer> lptr = make_unique<Layer>(_Size);
        Layer& retval = *lptr;
        _Layers.push_back(std::move(lptr));
        return retval;
    }

    Canvas::~Canvas()
    {

    }
}
