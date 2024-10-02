#include <iostream>
#include <vector>
#include <cstdint>
#include <cstdio>
#include <fstream>

#include "tests.hpp"
#include "cache.hpp"

int main(int argc, const char* argv[]) {

   run_tests(argv[1]);
}

int run_tests(const char* file_name) {

    uint64_t correct_test_count = 0;
    uint64_t num_elements       = 0;
    uint64_t cache_size         = 0;
    uint64_t hits_ref           = 0;
    uint64_t tests_num          = 0;

    //                      test.txt
    // [cache size] [number of elements] [elements] [reference hits value]
    // ...
   
   // FILE* file = fopen(file_name, "r"); 
   std::ifstream in_file(file_name);
    
    while (in_file >> cache_size) {

        in_file >> num_elements;
        ++tests_num;

        std::vector<int> test(num_elements);

        for (int i = 0; i < num_elements; ++i)
            if (!in_file >> test.at(i)) { 
                in_file.close();
                return 0;
            }

        if (!in_file >> hits_ref) {
            in_file.close();
            return 0;
        }

        Cache::Cache_2Q<int> cache(cache_size);
        uint64_t hits_counter = 0;

        for (int elem: test) 
            hits_counter += cache.cache_elem(elem);
    
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

    in_file.close();

    return 0;
}