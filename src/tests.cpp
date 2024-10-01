#include <iostream>
#include <vector>
#include <cstdint>
#include <cstdio>

//#include "tests.hpp"
#include "cache.hpp"

struct Test {
    uint64_t         cache_size;
    std::vector<int> elements;
    uint64_t         hits_num;
};

int main(int argc, char* argv[]) {

    uint64_t correct_test_count = 0;
    uint64_t num_elements       = 0;
    uint64_t cache_size         = 0;
    uint64_t hits_ref           = 0;
    uint64_t tests_num          = 0;

    //                      test.txt
    // [cache size] [number of elements] [elements] [reference hits value]
    // ...
   
    FILE* file = fopen(argv[1], "r"); 
    
    while (fscanf(file, "%llu", &cache_size) == 1) {

        if (fscanf(file, "%llu", &num_elements) != 1)
            return 0;

        ++tests_num;

        std::vector<int> test(num_elements);

        for (int i = 0; i < num_elements; ++i) {
            if (fscanf(file, "%d", &test.at(i)) != 1) 
                return 0;
        }

        if (fscanf(file, "%llu", &hits_ref) != 1)
            return 0;

        Cache::Cache_2Q<int> cache(cache_size);
        uint64_t hits_counter = 0;

        for (int elem: test) {
            std::cout << elem << '\n';
            hits_counter += cache.cache_elem(elem);
        }
        if (hits_counter != hits_ref) {
            std::cout << "test [" << tests_num << "] wrong\n";
            std::cout << "expected hits value = " << hits_ref 
                      << "\ncurrent value = " << hits_counter << '\n';
        }
        else 
            correct_test_count++;
    }

    if (correct_test_count == tests_num)
        std::cout << "--- All tests are correct ---\n";
}