#include "BrushesBase.hpp"

namespace cf
{
namespace Brushes
{

void Base::addProperty(std::string name, std::string def)
{
    _properties[name] = make_unique<Property<std::string> >(name, def);
}

Base::~Base()
{

}

}
}
