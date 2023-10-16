#include<iostream>
#include <math.h>
#include <chrono>
#include <unordered_set>

using namespace std;

int main(int argc, char *argv[]){
    auto t1 = std::chrono::high_resolution_clock::now();
    uint64_t trial = 1000000;
    unordered_set<string> s;
    for (uint64_t i = 0; i < trial; i++){
        s.insert(to_string(rand() % (trial)));
    }
    
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to add " << trial << " elements: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "ms" << std::endl;
    

    auto t3 = std::chrono::high_resolution_clock::now();
    uint64_t count = 0;
    for (uint64_t i = 0; i < trial; i++){
        if(s.find(to_string(rand() % (trial))) != s.end()){
            count++;
        }
    }
    auto t4 = std::chrono::high_resolution_clock::now();

    std::cout << "Time taken to check " << trial << " elements: " << std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count() << "ms" << std::endl;
    std::cout << "Percent of elements found: " << (double)count / trial << std::endl;
}