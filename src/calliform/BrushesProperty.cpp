#include "BrushesProperty.hpp"

namespace cf
{
namespace Brushes
{

AnyValue::~AnyValue()
{
}

AnyProperty::AnyProperty(const std::string name)
    : _name(std::move(name))
{
}

AnyProperty::~AnyProperty()
{
}

}
}
