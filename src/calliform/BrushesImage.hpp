#ifndef BRUSHESIMAGE_HPP
#define BRUSHESIMAGE_HPP 1

#include <SFML/Graphics.hpp>
#include "BrushesBase.hpp"
#include "BrushesProperty.hpp"

#include <iostream>

namespace cf
{
namespace Brushes
{

class Image : public Base
{
    BRUSH_REG_HEADER
private:
    unsigned int _diameter;
    std::string _source;
    bool _smooth;
    bool _repeat;

    sf::Texture _texture;
    float _scale;
public:
    static const std::string PROP_DIAMETER;
    static const std::string PROP_SOURCE;
    static const std::string PROP_SMOOTH;
    static const std::string PROP_REPEAT;
    Image();
    virtual void getProperty(const std::string& name, AnyValue& value) override;
    virtual void setProperty(const std::string& name, const AnyValue& value) override;
    virtual void prepare() override;
    virtual void render(sf::Sprite& sprite) const override;
};

}
}

#endif
