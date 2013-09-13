# Enable the testing framework
enable_testing()
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories(${INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRS})

add_executable(CalliformTest calliform_test.cpp)
target_link_libraries(CalliformTest gtest_main gtest ${CMAKE_THREAD_LIBS_INIT} calliform)
GTEST_ADD_TESTS(CalliformTest "" calliform_test.cpp)
