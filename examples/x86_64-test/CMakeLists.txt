cmake_minimum_required(VERSION 3.8)

set( UTILITY_DRIVER_PATH ../.. )

project(x64_64-test CXX)


add_executable(x64_64-test main.cpp)

add_subdirectory(${UTILITY_DRIVER_PATH} OmegaUtilityDriver)
target_link_libraries(x64_64-test OmegaUtilityDriver)
