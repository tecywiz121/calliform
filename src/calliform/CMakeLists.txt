# Find required packages
find_package(SFML COMPONENTS graphics window system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

# Build the core application
set(CMAKE_CXX_FLAGS "-g3 -Wall -Wextra -Werror -Wstrict-aliasing -std=c++11 -pedantic")

add_library(calliform SHARED calliform.cpp RenderPlane.cpp SFMLError.cpp Layer.cpp Canvas.cpp)
target_link_libraries(calliform ${SFML_LIBRARIES})
