#include "bloom.h"
#include "argh.h"
#include<iostream>
#include <math.h>
#include <chrono>

using namespace std;

int main(int argc, char *argv[]){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    argh::parser cmdl(argv);
    uint64_t n;
    uint32_t block_size;
    double error_order;
    cmdl("n", 10000) >> n; 
    cmdl("error_order", -2) >> error_order;
    cmdl("block_size", 4096) >> block_size;

    uint64_t m = (uint64_t)(-error_order * n * 5);


    std::cout<< "total bloom filter size: " << m << std::endl;
    std::cout<< "block size: " << block_size << std::endl;
    std::cout<< "block count: " << m / (block_size * 8) + 1 << std::endl;

    Bloom* bloom; 
    bloom = new Bloom("data/benchmark_bloom.bin", "data/benchmark_bloom.meta", m, n, block_size, 1LL<<32LL);

    auto t1 = std::chrono::high_resolution_clock::now();
    uint64_t trial = 100000;
    for (uint64_t i = 0; i < trial; i++){
        bloom->add(to_string(rand() % (trial)));
    }
    bloom->flush();
    
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to add " << trial << " elements: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms" << std::endl;
    

    auto t3 = std::chrono::high_resolution_clock::now();
    uint64_t count = 0;
    for (uint64_t i = 0; i < trial; i++){
        count += bloom->contains(to_string(rand() % (trial)));
    }
    auto t4 = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to check " << trial << " elements: " << std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count() << "ms" << std::endl;
    std::cout << "Percent of elements found: " << (double)count / trial << std::endl;


    delete bloom;
}