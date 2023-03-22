enable_testing()

find_package(GTest REQUIRED)

add_executable(sponsorship_test main.cpp)

target_link_libraries(sponsorship_test GTest::gtest sponsorship)

add_test(sponsorship_test COMMAND sponsorship_test)
