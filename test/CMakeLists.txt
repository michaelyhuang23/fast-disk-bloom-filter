cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(test_bloom test_bloom.cpp)

target_link_libraries(test_bloom
  fastbloom
  )


