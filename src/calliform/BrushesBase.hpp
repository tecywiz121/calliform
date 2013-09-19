#ifndef BRUSHESBASE_HPP
#define BRUSHESBASE_HPP 1

#include <string>
#include <memory>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "BrushesProperty.hpp"
#include "util.hpp"

namespace cf
{
namespace Brushes
{

class Base
{
private:
    std::unordered_map<std::string, std::unique_ptr<AnyProperty> > _properties;

protected:
    void addProperty(std::string name, std::string def);

    template<typename T>
    void addProperty(std::string name, T min, T max, T def)
    {
        _properties[name] = make_unique<Property<T> >(name, min, max, def);
    }

public:
    virtual void setProperty(const std::string& name, const AnyValue& value) =0;
    virtual void getProperty(const std::string& name, AnyValue& value) =0;
    virtual void render(sf::RenderTarget& target) const =0;
    virtual void prepare() =0;
    virtual ~Base();
};

}
}

#endif
