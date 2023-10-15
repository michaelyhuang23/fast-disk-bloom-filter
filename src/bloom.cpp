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

Bloom::Bloom(std::string _filename, std::string _meta_filename, uint64_t _size, uint64_t _expected_num_elements, uint32_t _block_size, int64_t _memory_limit) : 
    expected_num_elements(_expected_num_elements), 
    filename(_filename), 
    meta_filename(_meta_filename),
    block_size(_block_size), 
    num_blocks(_size / (block_size * BYTE_SIZE) + 1),
    memory_limit(_memory_limit)
{
    size = num_blocks * block_size * BYTE_SIZE;
    file = new FileManager(_filename, size, block_size);
    buffer_pool = BufferPool(file, _memory_limit, _block_size);
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
    buffer_pool = BufferPool(file, memory_limit, block_size);
}

Bloom::~Bloom(){
    buffer_pool.flush_all();
    delete file;
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
    buffer_pool.add(block_id, hashes);
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

    std::vector<bool> results(num_hashes);
    if(buffer_pool.query(block_id, hashes, results)){
        std::vector<uint32_t> r_hashes;
        for(size_t i=0;i<num_hashes;i++){
            if(!results[i]){
                r_hashes.push_back(hashes[i]);
            }
        }
        print_vector(r_hashes);
        return file->read_block(block_id * block_size, r_hashes);
    }else{
        return file->read_block(block_id * block_size, hashes);
    } 
}

uint64_t Bloom::getSize(){
    return size;
}