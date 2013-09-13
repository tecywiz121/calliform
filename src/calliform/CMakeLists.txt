# Build the core application
set(CMAKE_CXX_FLAGS "-g3 -Wall -Wextra -Werror -Wstrict-aliasing -std=c++11 -pedantic")

add_library(calliform SHARED calliform.cpp)
