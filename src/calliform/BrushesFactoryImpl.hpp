#ifndef BRUSHESFACTORYIMPL_HPP
#define BRUSHESFACTORYIMPL_HPP 1

#include "Canvas.hpp"
#include "BrushesFactory.hpp"

namespace cf
{
namespace Brushes
{

class Factory
{
    friend class cf::Canvas;
    friend Factory& getFactory();
    friend int _register(std::string, const BrushMakerFunc);
    friend void _deregister(int);
public:
    typedef std::unordered_map<int, const std::pair<const std::string, const BrushMakerFunc> > brush_map;

private:
    int _nextId = 0;
    brush_map _brushes;

    Factory();
    Factory(const Factory&);
    Factory(Factory&&);

    int registerBrush(std::string name, const BrushMakerFunc func);
    void deregisterBrush(int id);

    const brush_map& brushes() { return _brushes; }
};

Factory& getFactory();

}
}

#endif
