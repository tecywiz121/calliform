#include <utility>
#include "BrushesFactoryImpl.hpp"

namespace cf
{
namespace Brushes
{


Factory::Factory()
{

}

int Factory::registerBrush(std::string name, const BrushMakerFunc func)
{
    // TODO: This can roll around after max int and clobber existing brushes. Fix that.
    int id = _nextId++;
    _brushes.emplace(std::make_pair(id, std::make_pair(name, func)));
    return id;
}

void Factory::deregisterBrush(int id)
{
    _brushes.erase(id);
}

Factory& getFactory()
{
    // FOR INTERNAL USE ONLY!
    static Factory factory;
    return factory;
}

int _register(std::string name, const BrushMakerFunc func)
{
    return getFactory().registerBrush(std::move(name), func);
}

void _deregister(int id)
{
    getFactory().deregisterBrush(id);
}

}
}
