#ifndef CANVAS_HPP
#define CANVAS_HPP 1

#include <memory>
#include <list>
#include <SFML/Graphics.hpp>
#include "Layer.hpp"
#include "BrushesBase.hpp"
#include "util.hpp"

namespace cf
{
    class Canvas : sf::NonCopyable
    {
    public:
        typedef std::list<std::unique_ptr<Layer> > layer_list;

    private:
        sf::RenderTarget& _displayTarget;
        const sf::Vector2u _size;
        layer_list _layers;
        layer_list::const_iterator _activeLayer;

        std::vector<int> _brushes;
        std::unique_ptr<cf::Brushes::Base> _activeBrush;

    protected:
        // Is called when the canvas has finished drawing onto the DisplayTarget
        virtual void invalidate() =0;

    public:
        Canvas(sf::RenderTarget& displayTarget, sf::Vector2u size);

        sf::RenderTarget& displayTarget() const { return _displayTarget; }
        sf::Vector2u size() const { return _size; }

        const layer_list& layers() const { return _layers; }
        void activeLayer(layer_list::const_iterator value) { _activeLayer = value; }
        Layer& activeLayer() const { return **_activeLayer; }

        Layer& emplaceLayer(layer_list::const_iterator pos);
        void eraseLayer(layer_list::const_iterator pos);
        void eraseLayer(layer_list::const_iterator first, layer_list::const_iterator last);

        const std::vector<int>& brushes() const { return _brushes; }
        cf::Brushes::Base& activeBrush() const { return *_activeBrush; } // TODO: Ensure that the active brush hasn't been unloaded
        cf::Brushes::Base& activeBrush(int brushId);
        const std::string& brushName(int brushId);
        void scanBrushes();


        virtual ~Canvas();
    };
}

#endif
