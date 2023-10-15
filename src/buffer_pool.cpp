#include "buffer_pool.h"

BlockBuffer::BlockBuffer(uint64_t _block_id, std::vector<uint32_t>& hashes) : block_id(_block_id) {
    buffer = std::unordered_set<uint32_t>(hashes.begin(), hashes.end());
}

BlockBuffer::~BlockBuffer(){
    buffer.clear();
}

void BlockBuffer::query(std::vector<uint32_t>& hashes, std::vector<bool>& results){
    for(size_t i=0;i<hashes.size();i++){
        if(buffer.find(hashes[i]) == buffer.end()){
            results[i] = false;
        }else{
            results[i] = true;
        }
    }
}

void BlockBuffer::add(std::vector<uint32_t>& hashes){
    for(uint32_t hash : hashes){
        buffer.insert(hash);
    }
}

inline int64_t BlockBuffer::capacity(){
    return buffer.max_load_factor() * buffer.bucket_count() * sizeof(uint32_t);
}

void BlockBuffer::print(){
    std::cout << "block: " << block_id << std::endl;
    for(int hash : buffer){
        std::cout << hash << " ";
    }
    std::cout << std::endl;
}

BufferPool::BufferPool(): file(NULL), total_memory(0), memory_limit(0), block_size(0) {}

BufferPool::BufferPool(FileManager* _file, int64_t _memory_limit, uint32_t _block_size) : 
    file(_file), total_memory(0), memory_limit(_memory_limit), block_size(_block_size) 
{
    buffer_pool = std::vector<BlockBuffer*>();
    block_id_to_index = std::unordered_map<uint64_t, size_t>();
}

bool BufferPool::query(uint64_t block_id, std::vector<uint32_t>& hashes, std::vector<bool>& results){
    if(block_id_to_index.find(block_id) == block_id_to_index.end()){
        return false;
    }
    BlockBuffer* block_buffer = buffer_pool[block_id_to_index[block_id]];
    block_buffer->query(hashes, results);
    return true;
}

void BufferPool::add(uint64_t block_id, std::vector<uint32_t>& hashes){
    if(block_id_to_index.find(block_id) == block_id_to_index.end()){
        BlockBuffer* block_buffer = new BlockBuffer(block_id, hashes);
        buffer_pool.push_back(block_buffer);
        total_memory += block_buffer->capacity(); 
        block_id_to_index[block_id] = buffer_pool.size() - 1;
    }else{
        BlockBuffer* block_buffer = buffer_pool[block_id_to_index[block_id]];
        total_memory -= block_buffer->capacity();
        block_buffer->add(hashes);
        total_memory += block_buffer->capacity();
    }
    flush_last();
}

void BufferPool::flush_last(){
    while(total_memory > memory_limit){
        BlockBuffer* block_buffer = buffer_pool.back();
        total_memory -= block_buffer->capacity();
        flush_buffer(block_buffer);
        delete block_buffer;
        buffer_pool.pop_back();
    }
}

void BufferPool::flush_buffer(BlockBuffer* block_buffer){
    block_id_to_index.erase(block_buffer->block_id);
    // actually write to disk
    file->write_block(block_buffer->block_id * block_size, block_buffer->buffer);
}

void BufferPool::flush_all(){
    for(BlockBuffer* block_buffer : buffer_pool){
        flush_buffer(block_buffer);
        delete block_buffer;
    }
    buffer_pool.clear();
    block_id_to_index.clear();
}

BufferPool::~BufferPool(){
    flush_all();
}

void BufferPool::print(){
    std::cout << "buffer: " << std::endl;
    std::cout<< "total memory: " << total_memory << std::endl;
    for(auto it : block_id_to_index){
        std::cout << "block: " << it.first << " has index " << it.second << std::endl;
        buffer_pool[it.second]->print();
    }
}


