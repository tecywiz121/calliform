#ifndef LAYER_HPP
#define LAYER_HPP 1

#include <SFML/Graphics.hpp>
#include "RenderPlane.hpp"

namespace cf
{
    class Layer
    {
    private:
        RenderPlane _plane;
        sf::Color _tag;

    public:
        Layer(sf::Vector2u size);

        sf::Color tag() const { return _tag; }
        void tag(sf::Color tag) { _tag = tag; }

        sf::Vector2u size() const { return _plane.size(); }

        ~Layer();
    };
}

#endif
