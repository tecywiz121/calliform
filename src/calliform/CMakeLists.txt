# Get required libraries
find_package(PkgConfig REQUIRED)

pkg_check_modules(GTKMM gtkmm-3.0>=3.4 REQUIRED)

# Build the core application
set(CMAKE_CXX_FLAGS "-g3 -Wall -Wextra -Werror -Wstrict-aliasing -std=c++11 -pedantic")

add_library(calliform SHARED calliform.cpp)
