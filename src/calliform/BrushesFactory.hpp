#ifndef BRUSHESFACTORY_HPP
#define BRUSHESFACTORY_HPP 1

#include <memory>
#include <string>
#include <unordered_map>
#include "BrushesBase.hpp"

namespace cf
{
namespace Brushes
{

class Base;

typedef std::unique_ptr<Base> (*BrushMakerFunc)();

int _register(std::string name, const BrushMakerFunc func);
void _deregister(int id);


#define BRUSH_REG_HEADER                                                    \
class BrushInitializer                                                      \
{                                                                           \
private:                                                                    \
    int _id;                                                                \
    static std::unique_ptr<Base> construct();                               \
public:                                                                     \
    BrushInitializer();                                                     \
    ~BrushInitializer();                                                    \
};                                                                          \
static BrushInitializer _registerme;


#define BRUSH_REG(name)                                                     \
std::unique_ptr<Base> name::BrushInitializer::construct()                   \
{                                                                           \
    return make_unique<name>();                                             \
}                                                                           \
                                                                            \
name::BrushInitializer::BrushInitializer()                                  \
{                                                                           \
    std::cout << "BrushInitializer ";                                       \
    _id = _register(#name, &construct);                                     \
    std::cout << "(" << _id << ")" << std::endl;                            \
}                                                                           \
                                                                            \
name::BrushInitializer::~BrushInitializer()                                 \
{                                                                           \
    _deregister(_id);                                                       \
    std::cout << "BrushInitializer (dtor, " << _id << ")" << std::endl;     \
}                                                                           \
                                                                            \
name::BrushInitializer name::_registerme;                                   \
typedef class {} name##SwallowTheSemiColon

}
}

#endif
