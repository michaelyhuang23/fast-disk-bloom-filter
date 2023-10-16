#include "bloom.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(diskbloom, m) {
    py::class_<Bloom>(m, "Bloom")
        .def(py::init<std::string, std::string, uint64_t, double, uint32_t, int64_t>(), "create a bloom filter", py::arg("filename"), py::arg("meta_filename"), py::arg("expected_num_elements"), py::arg("error_order"), py::arg("block_size") = 4096, py::arg("memory_limit") = 2*1e9)
        .def(py::init<std::string, std::string>(), "read in a bloom filter", py::arg("filename"), py::arg("meta_filename"))
        .def("flush", &Bloom::flush, "flush writes to disk")
        .def("add", &Bloom::add, "add an element to the bloom filter", py::arg("s"))
        .def("contains", &Bloom::contains, "check if an element is in the bloom filter", py::arg("s"))
        .def("batchContains", &Bloom::batchContains, "check if a list of elements are in the bloom filter", py::arg("s"))
        .def("hash", &Bloom::hash, "all hash functions, 1-based index", py::arg("s"), py::arg("i"))
        .def("getSize", &Bloom::getSize, "get the size of the bloom filter");
}