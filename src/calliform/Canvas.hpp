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
        sf::RenderTarget& _DisplayTarget;
        std::vector<std::unique_ptr<Layer> > _Layers;
        const sf::Vector2u _Size;

    protected:
        // Is called when the canvas has finished drawing onto the DisplayTarget
        virtual void invalidate() =0;

    public:
        Canvas(sf::RenderTarget& displayTarget, sf::Vector2u size);

        sf::RenderTarget& DisplayTarget() const { return _DisplayTarget; }
        sf::Vector2u Size() const { return _Size; }

        const std::vector<std::unique_ptr<Layer> >& Layers() const { return _Layers; }

        Layer& PushLayer();

        virtual ~Canvas();
    };
}

#endif
