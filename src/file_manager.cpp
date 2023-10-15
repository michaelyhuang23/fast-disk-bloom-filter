#include "file_manager.h"

void print_set(std::unordered_set<uint32_t>& s){
    for(uint32_t i : s){
        std::cout<< i << " ";
    }
    std::cout<<std::endl;
}

FileManager::FileManager() : file(NULL), file_path(""), size(0){}

FileManager::FileManager(std::string _file_path, uint64_t _size, uint32_t _block_size): 
    size(_size), block_size(_block_size)
{
    file_path = _file_path;
    file = fopen(file_path.c_str(), "rb+"); // reading and writing in binary mode

    if(file == NULL){
        file = fopen(file_path.c_str(), "wb+");
        assert(file != NULL);
        std::cout<< "Creating new file " << file_path << std::endl;
        fseek(file, size / BYTE_SIZE + tail_size - 1, SEEK_SET);
        fwrite("", 1, 1, file);
        fseek(file, 0, SEEK_SET);
    }

    check_file();
}

void FileManager::check_file(){
    fseek(file, 0, SEEK_END); 
    uint64_t c_size = ftell(file); 
    std::cout<< "File size: " << c_size << std::endl;
    std::cout<< "Expected size: " << size / BYTE_SIZE + tail_size << std::endl;
    assert(c_size == size / BYTE_SIZE + tail_size);
    fseek(file, 0, SEEK_SET);
}

FileManager::~FileManager(){
    fclose(file);
}

void FileManager::write_block(uint64_t byte_offset, std::unordered_set<uint32_t>& hashes){
    std::cout<< "Writing block at " << byte_offset << std::endl;
    print_set(hashes);
    fseek(file, byte_offset, SEEK_SET);
    unsigned char c_byte[block_size];
    fread(c_byte, 1, block_size, file);
    for(uint32_t bit_index : hashes){
        c_byte[bit_index / BYTE_SIZE] |= (1 << (bit_index % BYTE_SIZE)); 
    }
    fseek(file, byte_offset, SEEK_SET);
    fwrite(c_byte, 1, block_size, file);
}

bool FileManager::read_block(uint64_t byte_offset, std::vector<uint32_t>& hashes){
    fseek(file, byte_offset, SEEK_SET);
    unsigned char c_byte[block_size];
    fread(c_byte, 1, block_size, file);
    for(uint32_t bit_index : hashes){
        if(!(c_byte[bit_index / BYTE_SIZE] & (1 << (bit_index % BYTE_SIZE)))){
            return false;
        }
    }
    return true;
}

//void FileManager::write_block(int byte_offset, std::unordered_set<int>& hashes){
//    fseek(file, byte_offset, SEEK_SET);
//    int p_byte_index = 0;
//    unsigned char c_byte;
//    for(int bit_index : hashes){
//        std::cout<< ftell(file) - byte_offset << std::endl;
//        fseek(file, bit_index / BYTE_SIZE - p_byte_index, SEEK_CUR);
//        std::cout<< bit_index / BYTE_SIZE << " " << ftell(file) - byte_offset << std::endl;
//        p_byte_index = bit_index / BYTE_SIZE;
//        fread(&c_byte, 1, 1, file);
//        std::cout<< ftell(file) - byte_offset << std::endl;
//        c_byte |= (1 << (bit_index % BYTE_SIZE)); 
//        // note the residual bit index is counted backwards for convenience
//        std::cout<<fwrite(&c_byte, 1, 1, file)<<std::endl;
//        std::cout<< ftell(file) - byte_offset << std::endl;
//    }
//}

//bool FileManager::read_block(int byte_offset, std::vector<int>& hashes){
//    fseek(file, byte_offset, SEEK_SET);
//    int p_byte_index = 0;
//    unsigned char c_byte;
//    for(int bit_index : hashes){
//        fseek(file, bit_index / BYTE_SIZE - p_byte_index, SEEK_CUR);
//        p_byte_index = bit_index / BYTE_SIZE;
//        fread(&c_byte, 1, 1, file);
//        if(!(c_byte & (1 << (bit_index % BYTE_SIZE)))){
//            return false;
//        }
//    }
//    return true;
//}