#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<bitset>
#include<numeric>
#include<fstream>

#include "buffer_pool.h"
#include "file_manager.h"
#include "MurmurHash3.h"

#define BYTE_SIZE 8
// over flow might occur if the number of elements is too large

class Bloom{
    public: 
        ~Bloom();
        Bloom(std::string _filename, std::string _meta_filename, uint64_t _size, uint64_t _expected_num_elements, uint32_t _block_size = 4096, int64_t _memory_limit = 2*1e9);
        Bloom(std::string _filename, std::string _meta_filename);
        void add(std::string s);
        bool contains(std::string s);
        uint32_t hash(std::string s, uint64_t i);
        uint64_t getSize();
    private:
        uint64_t size;
        uint64_t num_hashes;
        uint64_t expected_num_elements;
        std::string filename;
        std::string meta_filename;
        uint32_t block_size = 4096;
        uint64_t num_blocks;
        int64_t memory_limit = 2*1e9;
        BufferPool buffer_pool;
        FileManager* file;
        std::vector<uint32_t> hash_seeds;

        void write_metafile();
        void read_metafile();
};