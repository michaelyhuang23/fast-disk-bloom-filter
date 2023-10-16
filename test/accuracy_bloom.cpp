#include "bloom.h"
#include "argh.h"
#include<iostream>
#include <math.h>
#include <chrono>
#include "parlay/parallel.h"

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
    bloom = new Bloom(m, "data/accuracy_bloom.bin", "data/accuracy_bloom.meta", n, block_size, 1LL<<32LL);

    auto t1 = std::chrono::high_resolution_clock::now();
    uint64_t trial = n;
    unordered_set<string> s;
    for (uint64_t i = 0; i < trial; i++){
        uint64_t x = rand() % (trial);
        bloom->add(to_string(x));
        s.insert(to_string(x));
    }
    bloom->flush();
    
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to add " << trial << " elements: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms" << std::endl;
    

    std::vector<std::string> strs(trial);

    auto t3 = std::chrono::high_resolution_clock::now();
    uint64_t w_count = 0;
    for (uint64_t i = 0; i < trial; i++){
        uint64_t x = rand() % (trial);
        strs[i] = to_string(x);
        bool p_contain = bloom->contains(to_string(x));
        if(p_contain != (s.find(to_string(x)) != s.end())){
            w_count++;
        }
    }
    auto t4 = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to check " << trial << " elements: " << std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count() << "ms" << std::endl;
    std::cout << "Percent of mistakes: " << (double)w_count / trial << std::endl;


    w_count = 0;

    auto t5 = std::chrono::high_resolution_clock::now();
    std::vector<bool> results = bloom->batchContains(strs);
    auto t6 = std::chrono::high_resolution_clock::now();

    for(uint64_t i=0;i<trial;i++){
        bool p_contain = results[i];
        if(p_contain != (s.find(strs[i]) != s.end()))
            w_count ++;
    }

    std::cout << "Time taken to batch check " << trial << " elements: " << std::chrono::duration_cast<std::chrono::milliseconds>(t6 - t5).count() << "ms" << std::endl;
    std::cout << "Batch check percent of mistakes: " << (double)w_count / trial << std::endl;
    delete bloom;
}