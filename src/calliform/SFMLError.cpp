#include <SFMLError.hpp>

namespace cf
{
    SFMLError::SFMLError(const std::string& what_arg)
        : runtime_error(what_arg)
    {

    }

    SFMLError::SFMLError(const char* what_arg)
        : runtime_error(what_arg)
    {

    }
}
