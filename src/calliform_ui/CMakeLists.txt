# Get required libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-3.0>=3.4 REQUIRED)

set(CMAKE_CXX_FLAGS "-g3 -Wall -Wextra -Werror -Wstrict-aliasing -std=c++11 -pedantic")

link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})

add_executable(calliform_ui calliform_ui.cpp SFMLWidget.cpp)
target_link_libraries(calliform_ui calliform ${GTKMM_LIBRARIES})
