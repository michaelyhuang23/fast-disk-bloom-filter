cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(test_bloom test_bloom.cpp)
add_executable(benchmark_bloom benchmark_bloom.cpp)
add_executable(accuracy_bloom accuracy_bloom.cpp)
add_executable(benchmark_unordered_set benchmark_unordered_set.cpp)

target_link_libraries(test_bloom
  fastbloom
  )

target_link_libraries(benchmark_bloom
  fastbloom
  )

target_link_libraries(accuracy_bloom
  fastbloom
  )

target_link_libraries(benchmark_unordered_set
  fastbloom
  )