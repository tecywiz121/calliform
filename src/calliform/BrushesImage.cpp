#include <limits>
#include <stdexcept>
#include "BrushesImage.hpp"
#include "SFMLError.hpp"

namespace cf
{
namespace Brushes
{

const std::string Image::PROP_DIAMETER = "Diameter";
const std::string Image::PROP_SOURCE = "Source";
const std::string Image::PROP_SMOOTH = "Smoothed";
const std::string Image::PROP_REPEAT = "Repeated";

Image::Image()
{
    addProperty(PROP_DIAMETER, 0U, std::numeric_limits<unsigned int>::max(), 1U);
    addProperty(PROP_SOURCE, "");
    addProperty(PROP_SMOOTH, false, true, false);
    addProperty(PROP_REPEAT, false, true, false);
}

void Image::getProperty(const std::string& name, AnyValue& value)
{
    if (name == PROP_DIAMETER)
    {
        dynamic_cast<Value<unsigned int>& >(value).set(_diameter);
    }
    else if (name == PROP_SOURCE)
    {
        dynamic_cast<Value<std::string>& >(value).set(_source);
    }
    else if (name == PROP_SMOOTH)
    {
        dynamic_cast<Value<bool>& >(value).set(_smooth);
    }
    else if (name == PROP_REPEAT)
    {
        dynamic_cast<Value<bool>& >(value).set(_repeat);
    }
    else
    {
        throw std::out_of_range("unknown property name");
    }
}

void Image::setProperty(const std::string& name, const AnyValue& value)
{
    if (name == PROP_DIAMETER)
    {
        _diameter = dynamic_cast<const Value<unsigned int>& >(value).get();
    }
    else if (name == PROP_SOURCE)
    {
        _source = dynamic_cast<const Value<std::string>& >(value).get();
    }
    else if (name == PROP_SMOOTH)
    {
        _smooth = dynamic_cast<const Value<bool>& >(value).get();
    }
    else if (name == PROP_REPEAT)
    {
        _repeat = dynamic_cast<const Value<bool>& >(value).get();
    }
    else
    {
        throw std::out_of_range("unknown property name");
    }
}

void Image::prepare()
{
    // Load the texture from the given file
    if (!_texture.loadFromFile(_source))
    {
        throw SFMLError("unable to load texture");
    }

    // Set texture properties
    _texture.setSmooth(_smooth);
    _texture.setRepeated(_repeat);

    // Resize the sprite to fit in the diameter
    sf::Vector2u texSize = _texture.getSize();
    unsigned int longSide = std::max(texSize.x, texSize.y);
    _scale = (float)_diameter / (float)longSide;
}

void Image::render(sf::Sprite& sprite) const
{
    sprite.setScale(_scale, _scale);
    sprite.setTexture(_texture);
}

}
}
