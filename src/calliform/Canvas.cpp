#include <memory>
#include "Canvas.hpp"
#include "util.hpp"

namespace cf
{
    Canvas::Canvas(sf::RenderTarget& displayTarget, sf::Vector2u size)
        : _displayTarget(displayTarget), _size(size)
    {

    }

    Layer& Canvas::pushLayer()
    {
        std::unique_ptr<Layer> lptr = make_unique<Layer>(_size);
        Layer& retval = *lptr;
        _layers.push_back(std::move(lptr));
        return retval;
    }

    Canvas::~Canvas()
    {

    }
}
