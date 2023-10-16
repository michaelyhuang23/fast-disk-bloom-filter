#include "bloom.h"



void print_vector(std::vector<uint32_t>& v){
    for(uint32_t i=0;i<v.size();i++){
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

void Bloom::write_metafile(){
    std::ofstream meta_file(meta_filename);
    meta_file << size << '\n';
    meta_file << expected_num_elements << '\n';
    meta_file << num_hashes << '\n';
    meta_file << num_blocks << '\n';
    meta_file << block_size << '\n';
    meta_file << memory_limit << '\n';
    for(size_t i=0;i<num_hashes+1;i++){
        meta_file << hash_seeds[i] << ' ';
    }
    meta_file << std::endl;
    meta_file.close();
}

void Bloom::read_metafile(){
    std::ifstream meta_file(meta_filename);
    meta_file >> size;
    meta_file >> expected_num_elements;
    meta_file >> num_hashes;
    meta_file >> num_blocks;
    meta_file >> block_size;
    meta_file >> memory_limit;
    hash_seeds = std::vector<uint32_t>(num_hashes+1);
    for(size_t i=0;i<num_hashes+1;i++){
        meta_file >> hash_seeds[i];
    }
    meta_file.close();
}

Bloom::Bloom(std::string _filename, std::string _meta_filename, uint64_t _expected_num_elements, double _error_order, uint32_t _block_size, int64_t _memory_limit)
    : expected_num_elements(_expected_num_elements), 
    filename(_filename), 
    meta_filename(_meta_filename),
    block_size(_block_size),
    memory_limit(_memory_limit)
{
    uint64_t _size = (uint64_t)(- _error_order * _expected_num_elements * 5);
    num_blocks = _size / (block_size * BYTE_SIZE) + 1;
    size = num_blocks * block_size * BYTE_SIZE;
    file = new FileManager(_filename, size, block_size);
    num_hashes = (int64_t) (0.7 * size / expected_num_elements);
    hash_seeds = std::vector<uint32_t>(num_hashes+1);
    for(size_t i=0;i<num_hashes+1;i++){
        hash_seeds[i] = rand();
    }

    write_metafile();
}

Bloom::Bloom(uint64_t _size, std::string _filename, std::string _meta_filename, uint64_t _expected_num_elements, uint32_t _block_size, int64_t _memory_limit) : 
    expected_num_elements(_expected_num_elements), 
    filename(_filename), 
    meta_filename(_meta_filename),
    block_size(_block_size), 
    num_blocks(_size / (block_size * BYTE_SIZE) + 1),
    memory_limit(_memory_limit)
{
    size = num_blocks * block_size * BYTE_SIZE;
    file = new FileManager(_filename, size, block_size);
    num_hashes = (int64_t) (0.7 * size / expected_num_elements);
    hash_seeds = std::vector<uint32_t>(num_hashes+1);
    for(size_t i=0;i<num_hashes+1;i++){
        hash_seeds[i] = rand();
    }

    // write meta file
    write_metafile();
}

Bloom::Bloom(std::string _filename, std::string _meta_filename) : 
    filename(_filename), 
    meta_filename(_meta_filename)
{
    read_metafile();
    file = new FileManager(_filename, size, block_size);
}

Bloom::~Bloom(){
    delete file;
}

void Bloom::flush(){
    file->flush();
}

uint32_t Bloom::hash(std::string s, uint64_t i){
    uint32_t hash;
    MurmurHash3_x86_32(s.c_str(), s.size(), hash_seeds[i], &hash);
    return hash;
}

void Bloom::add(std::string s){
    std::vector<uint32_t> hashes(num_hashes);
    for(size_t i = 0; i < num_hashes; i++){
        hashes[i] = hash(s, i+1) % (block_size * BYTE_SIZE);
    }
    uint64_t block_id = hash(s, 0) % num_blocks;
    file->write_block(block_id * block_size, hashes);
}

bool Bloom::contains(std::string s){
    std::vector<uint32_t> hashes(num_hashes);
    for(size_t i = 0; i < num_hashes; i++){
        hashes[i] = hash(s, i+1) % (block_size * BYTE_SIZE);
    }
    uint64_t block_id = hash(s, 0) % num_blocks;
    //std::cout << "block_id: " << block_id << std::endl;
    //print_vector(hashes);
    //std::cout << "----" << std::endl;
    return file->read_block(block_id * block_size, hashes);
}

//void Bloom::batchContains(std::vector<std::string>& items, std::vector<bool>& results){
//    #pragma omp parallel for
//    for(size_t i = 0; i < items.size(); i++){
//        uint64_t offset = (hash(items[i], 0) % num_blocks) * block_size;
//        std::vector<uint32_t> hashes(num_hashes);
//        for(size_t j = 0; j < num_hashes; j++){
//            hashes[j] = hash(items[i], j+1) % (block_size * BYTE_SIZE);
//        }
//        results[i] = file->read_block(offset, hashes);
//    }
//}

std::vector<bool> Bloom::batchContains(std::vector<std::string>& items){
    std::vector<bool> results(items.size());
    std::vector<uint64_t> offsets(items.size());
    std::vector<std::vector<uint32_t>> hashes(items.size(), std::vector<uint32_t>(num_hashes));

    parlay::parallel_for(0, items.size(), [&](size_t i){
        offsets[i] = (hash(items[i], 0) % num_blocks) * block_size;
        for(size_t j = 0; j < num_hashes; j++){
            hashes[i][j] = hash(items[i], j+1) % (block_size * BYTE_SIZE);
        }
    });

    file->batch_read_block(offsets, hashes, results);
    return results;
}

uint64_t Bloom::getSize(){
    return size;
}

