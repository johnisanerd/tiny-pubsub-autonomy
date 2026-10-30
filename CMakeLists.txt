cmake_minimum_required(VERSION 3.20)
project(tiny_pubsub_autonomy CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(drone_sim src/main.cpp)
target_compile_options(drone_sim PRIVATE -Wall -Wextra -Wpedantic)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(sim_test tests/sim_test.cpp)
target_link_libraries(sim_test GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(sim_test)