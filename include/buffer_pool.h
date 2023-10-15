#pragma once

#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<iostream>
#include<stdio.h>

#include "file_manager.h"

struct BlockBuffer{
    std::unordered_set<uint32_t> buffer;
    uint64_t block_id;
    BlockBuffer(uint64_t _block_id, std::vector<uint32_t>& hashes);
    ~BlockBuffer();
    void query(std::vector<uint32_t>& hashes, std::vector<bool>& results); 
    void add(std::vector<uint32_t>& hashes);
    inline int64_t capacity();
    void print();
};

class BufferPool{
    public:
        BufferPool();
        ~BufferPool();
        BufferPool(FileManager* _file, int64_t _memory_limit, uint32_t _block_size);
        bool query(uint64_t block_id, std::vector<uint32_t>& hashes, std::vector<bool>& results); 
        void add(uint64_t block_id, std::vector<uint32_t>& hashes);
        void flush_last();
        void flush_buffer(BlockBuffer* block_buffer);
        void flush_all();
        void print();
    private:
        std::unordered_map<uint64_t, size_t> block_id_to_index;
        std::vector<BlockBuffer*> buffer_pool;
        int64_t total_memory;
        int64_t memory_limit;
        uint32_t block_size;
        FileManager* file;
};