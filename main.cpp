#include <iostream>

#include "tests.hpp"
#include "cache.hpp"

int main()
{
    uint64_t cache_size = 0;
    uint64_t number_of_elements = 0;
    
    #ifdef Debug
        std::cout << "Input the size of cache\n";
    #endif
    std::cin >> cache_size;
    #ifdef Debug
        std::cout << cache_size << std::endl;
    #endif
    //cache.create_cache(cache_size);
    Cache::Cache_2Q<int> cache(cache_size);
    #ifdef Debug
        std::cout << "Input the number of elements\n";
    #endif
    std::cin >> number_of_elements;
    #ifdef Debug
        std::cout << "Input elements" << std::endl;
    #endif

    uint64_t new_elem = 0;
    uint64_t hits_counter = 0, num = 0;
    for (uint64_t i = 0; i < number_of_elements; ++i) {
        std::cin >> new_elem;
        num++;
        #ifdef Debug
            std::cout << new_elem << std::endl;
        #endif
        hits_counter += cache.cache_elem(new_elem);
    }
    // cache.clear();

    std::cout << hits_counter << '\n';
    #ifdef Debug
        uint64_t result = (double) hits_counter / (double) num * 100;
        std::cout << result << "%\n";  
    #endif
}