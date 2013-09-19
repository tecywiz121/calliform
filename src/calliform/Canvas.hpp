#ifndef CANVAS_HPP
#define CANVAS_HPP 1

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Layer.hpp"

namespace cf
{
    class Canvas : sf::NonCopyable
    {
    private:
        sf::RenderTarget& _displayTarget;
        std::vector<std::unique_ptr<Layer> > _layers;
        const sf::Vector2u _size;

    protected:
        // Is called when the canvas has finished drawing onto the DisplayTarget
        virtual void invalidate() =0;

    public:
        Canvas(sf::RenderTarget& displayTarget, sf::Vector2u size);

        sf::RenderTarget& displayTarget() const { return _displayTarget; }
        sf::Vector2u size() const { return _size; }

        const std::vector<std::unique_ptr<Layer> >& layers() const { return _layers; }

        Layer& pushLayer();

        virtual ~Canvas();
    };
}

#endif
