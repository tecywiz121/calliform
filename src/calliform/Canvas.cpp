#include <memory>
#include "Canvas.hpp"
#include "BrushesFactoryImpl.hpp"
#include "util.hpp"


namespace cf
{
    Canvas::Canvas(sf::RenderTarget& displayTarget, sf::Vector2u size)
        : _displayTarget(displayTarget), _size(size)
    {

    }

    Layer& Canvas::emplaceLayer(layer_list::const_iterator pos)
    {
        return **_layers.emplace(remove_constness(_layers, pos),
                                    make_unique<Layer>(_size));
    }

    void Canvas::eraseLayer(layer_list::const_iterator pos)
    {
        _layers.erase(remove_constness(_layers, pos));
    }

    void Canvas::eraseLayer(layer_list::const_iterator first,
                            layer_list::const_iterator last)
    {
        _layers.erase(remove_constness(_layers, first),
                        remove_constness(_layers, last));
    }

    void Canvas::scanBrushes()
    {
        // Invalidates brush references!
        _brushes.clear();

        cf::Brushes::Factory& factory = cf::Brushes::getFactory();

        for (auto kvp : factory.brushes())
        {
            _brushes.emplace_back(kvp.first);
        }
    }

    cf::Brushes::Base& Canvas::activeBrush(int brushId)
    {
        // TODO: Maybe keep around the last couple used brushes
        cf::Brushes::Factory& factory = cf::Brushes::getFactory();
        auto& brushes = factory.brushes();
        auto& brushInfo = brushes.at(brushId);

        _activeBrush = std::unique_ptr<cf::Brushes::Base>(brushInfo.second());
        return *_activeBrush;
    }

    const std::string& Canvas::brushName(int brushId)
    {
        // TODO: Maybe keep around the last couple used brushes
        cf::Brushes::Factory& factory = cf::Brushes::getFactory();
        auto& brushes = factory.brushes();
        auto& brushInfo = brushes.at(brushId);

        return brushInfo.first;
    }

    Canvas::~Canvas()
    {

    }
}
