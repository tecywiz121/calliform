#ifndef BRUSHESPROPERTY_HPP
#define BRUSHESPROPERTY_HPP 1

#include <typeindex>
#include <string>

namespace cf
{
namespace Brushes
{

class AnyValue
{
public:
    virtual ~AnyValue();

    virtual std::type_index type() =0;
};

template<typename T>
class Value : public AnyValue
{
    static_assert(std::is_arithmetic<T>::value,
                    "T must be an arithmetic type, or a string");
private:
    T _value;

public:
    T get() const { return _value; }
    void set(T v) { _value = std::move(v); }
    virtual std::type_index type() override { return typeid(T); }
};

template<>
class Value<std::string> : public AnyValue
{
private:
    std::string _value;

public:
    const std::string& get() const { return _value; }
    void set(std::string v) { _value = std::move(v); }
    virtual std::type_index type() override { return typeid(std::string); }
};

class AnyProperty
{
private:
    const std::string _name;

public:
    const std::string& name();
    virtual std::type_index type() =0;

    AnyProperty(const std::string name);
    virtual ~AnyProperty();
};

template<typename T>
class Property : public AnyProperty
{
    static_assert(std::is_arithmetic<T>::value,
                    "T must be an arithmetic type, or a string");
private:
    const T _initial;
    const T _max;
    const T _min;

public:
    T initial() { return _initial; }
    T max() { return _max; }
    T min() { return _min; }
    virtual std::type_index type() override { return typeid(T); }

    Property(const std::string name, const T min, const T max, const T initial)
        : AnyProperty(std::move(name)), _initial(initial), _max(max), _min(min)
    {

    }
};

template<>
class Property<std::string> : public AnyProperty
{
private:
    const std::string _initial;

public:
    const std::string& initial() { return _initial; }
    virtual std::type_index type() override { return typeid(std::string); }

    Property(std::string name, std::string initial)
        : AnyProperty(std::move(name)), _initial(std::move(initial))
    {

    }
};

template class Property<int>;
template class Property<std::string>;
template class Value<int>;
template class Value<std::string>;
}
}

#endif
