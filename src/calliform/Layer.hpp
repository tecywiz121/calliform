#ifndef LAYER_HPP
#define LAYER_HPP 1

#include <SFML/Graphics.hpp>
#include "RenderPlane.hpp"

namespace cf
{
    class Layer
    {
    private:
        RenderPlane _Plane;
        sf::Color _Tag;

    public:
        Layer(sf::Vector2u size);

        sf::Color Tag() const { return _Tag; }
        void Tag(sf::Color tag) { _Tag = tag; }

        sf::Vector2u Size() const { return _Plane.Size(); }

        ~Layer();
    };
}

#endif
