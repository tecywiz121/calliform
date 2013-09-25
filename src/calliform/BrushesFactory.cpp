#include <utility>
#include "BrushesFactory.hpp"

namespace cf
{
namespace Brushes
{

class Factory;

static Factory& getFactory();

class Factory
{
    friend Factory& getFactory();
    friend int _register(std::string, const BrushMakerFunc);
    friend void _deregister(int);
private:
    int _nextId = 0;
    std::unordered_map<int, const std::pair<const std::string, const BrushMakerFunc> > _brushes;

    Factory();
    Factory(const Factory&);
    Factory(Factory&&);

    int registerBrush(std::string name, const BrushMakerFunc func);
    void deregisterBrush(int id);
};

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

static Factory& getFactory()
{
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
