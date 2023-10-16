#include "bloom.h"
#include "argh.h"
#include<iostream>

using namespace std;

int main(int argc, char *argv[]){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    argh::parser cmdl(argv);
    std::string filename = cmdl("file").str();
    std::string meta_filename = cmdl("meta").str();

    std::cout << "file: " << filename << std::endl;
    std::cout << "meta: " << meta_filename << std::endl;

    if(cmdl["help"] || filename == "" || meta_filename == ""){
        cout << "Usage: ./test_bloom --file=<filename> --meta=<meta_filename> [--create]" << endl;
        return 0;
    }
    
    Bloom* bloom; 
    if(cmdl["create"]){
        std::cout<< "Creating new bloom filter" << std::endl;
        bloom = new Bloom(10000LL, filename, meta_filename, 1000LL, 128, 100);
    }else{
        std::cout<< "Loading existing bloom filter" << std::endl;
        bloom = new Bloom(filename, meta_filename);
    }

    while(true){
        // read a line from input, if operation is add, add element to bloom. Other wise query
        string operation, element;
        cin >> operation >> element;
        if(operation == "add"){
            bloom->add(element);
        }else if(operation == "query"){
            cout << bloom->contains(element) << endl;
        }else{
            break;
        }
    }

    delete bloom;
}