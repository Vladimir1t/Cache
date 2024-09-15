#include <iostream>

#include "tests.hpp"
#include "cache.hpp"

//#define

int main()
{
    std::cout << "\n-------------------- Cache --------------------\n\n";

    Cache_class<int> cache;

    uint64_t cache_size = 0;
    uint64_t number_of_elements = 0;

    std::cout << "Input the size of cache\n";
    std::cin >> cache_size;
    //std::cout << cache_size << '\n';
    cache.create_cache(cache_size);

    std::cout << "Input the number of elements\n";
    std::cin >> number_of_elements;

    std::cout << "Input elements\n";

    uint64_t new_elem = 0;
    uint64_t hits_counter = 0, num = 0;
    for (uint64_t i = 0; i < number_of_elements; ++i) {
        std::cin >> new_elem;
        num++;
        //std::cout << new_elem << '\n';
        hits_counter += cache.cache_elem(new_elem);
    }
    cache.clear();

    std::cout << "number of strikes = " << hits_counter << '\n';
    uint64_t result = (double) hits_counter / (double) num * 100;
    std::cout << result << "% \n";   

    run_tests(); 
}