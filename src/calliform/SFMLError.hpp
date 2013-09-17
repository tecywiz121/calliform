#ifndef SFMLEXCEPTION_HPP
#define SFMLEXCEPTION_HPP 1

#include <exception>
#include <stdexcept>

namespace cf
{
    class SFMLError : public std::runtime_error
    {
    public:
        SFMLError(const char* what_arg);
        SFMLError(const std::string& what_arg);
    };
}

#endif
