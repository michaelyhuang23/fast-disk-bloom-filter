#pragma once

#include<stdio.h>
#include<vector>
#include<unordered_set>
#include<string>
#include<iostream>
#include<assert.h>

#define BYTE_SIZE 8

class FileManager{
    public:
        FileManager();
        FileManager(std::string _file_path, uint64_t _size, uint32_t _block_size);
        void write_block(uint64_t byte_offset, std::vector<uint32_t>& hashes);
        bool read_block(uint64_t byte_offset, std::vector<uint32_t>& hashes);
        void check_file();
        ~FileManager();
    private:
        FILE* file;
        std::string file_path;
        uint64_t size;
        uint32_t block_size;
        const uint32_t tail_size = 8;
};
