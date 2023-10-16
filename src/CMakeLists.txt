add_library(fastbloom bloom.cpp file_manager.cpp MurmurHash3.cpp) 
target_include_directories(fastbloom PUBLIC ${CMAKE_SOURCE_DIR}/include)

pybind11_add_module(diskbloom binding.cpp)
target_link_libraries(diskbloom PRIVATE fastbloom)