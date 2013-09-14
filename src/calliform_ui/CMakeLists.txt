# Get required libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-3.0>=3.4 REQUIRED)

find_package(SFML COMPONENTS graphics window system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "-g3 -Wall -Wextra -Werror -Wstrict-aliasing -std=c++11 -pedantic")

link_directories(${LINK_DIRECTORIES} ${GTKMM_LIBRARY_DIRS})
include_directories(${INCLUDE_DIRECTORIES} ${GTKMM_INCLUDE_DIRS})

add_executable(calliform_ui calliform_ui.cpp SFMLWidget.cpp)
target_link_libraries(calliform_ui ${SFML_LIBRARIES} ${GTKMM_LIBRARIES})
