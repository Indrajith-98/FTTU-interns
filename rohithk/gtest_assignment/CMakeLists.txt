cmake_minimum_required( VERSION 3.28.3 )
project( gtest)

option(CODE_COVERAGE "Enable code coverage" ON)

if(CODE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -g")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage -g")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lgcov")
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories( include test_coverage/tests )

# add_executable(
#   unit_test
#   test_coverage/unit_test.cc
#   )
add_executable(unit_test
    test_coverage/tests/factorial_tests.cpp
    test_coverage/tests/fibonacci_tests.cpp
    test_coverage/tests/gcd_tests.cpp
    test_coverage/tests/lcm_tests.cpp
    test_coverage/tests/prime_factors_tests.cpp
    test_coverage/tests/calculate_pi_tests.cpp
    test_coverage/tests/sigmoid_tests.cpp
    test_coverage/tests/relu_tests.cpp
    test_coverage/tests/mean_squared_error_tests.cpp
    test_coverage/main.cc)

add_library( my_math src/my_math.cpp )

target_link_libraries(  unit_test GTest::gtest_main my_math  gcov)
  
target_include_directories( my_math PUBLIC include test_coverage/tests )




include(GoogleTest include)

gtest_discover_tests(unit_test)
