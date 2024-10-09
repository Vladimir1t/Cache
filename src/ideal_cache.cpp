#include <iostream>
#include <vector>
#include <cstdint>

#include "ideal_cache.hpp"


int main() {

    uint64_t cache_size = 0;
    uint64_t number_of_elements = 0;
    uint64_t hits_counter = 0;

   #ifndef NDEBUG
        std::cout << "Input the size of cache\n";
    #endif
    std::cin >> cache_size;
    #ifndef NDEBUG
        std::cout << cache_size << '\n';
    #endif
    Cache::Ideal_cache<int> ideal_cache(cache_size);
    #ifndef NDEBUG
        std::cout << "Input the number of elements\n";
    #endif
    std::cin >> number_of_elements;
    #ifndef NDEBUG
        std::cout << "Input elements\n";
    #endif

    std::vector<int> elements;
    uint64_t new_elem = 0;
  
    for (uint64_t i = 0; i < number_of_elements; ++i) {
        std::cin >> new_elem;
        elements.push_back(new_elem);
    }
    hits_counter = ideal_cache.run_ideal_cache(elements);
        
    std::cout << hits_counter << '\n';
}