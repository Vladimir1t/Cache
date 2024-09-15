#include <iostream>

#include "tests.hpp"
#include "cache.hpp"

int main()
{
    std::cout << "\n-------------------- Cache --------------------\n\n";

    Cache_class<int> cache;
    uint64_t cache_size = 0;
    std::cout << "Input the size of cache\n";
    std::cin >> cache_size;
    cache.create_cache(cache_size);

    std::cout << "Input elements\n";

    uint64_t new_elem = 0;
    uint64_t hits_counter = 0, num = 0;
    while ((std::cin >> new_elem) && !isalpha(new_elem)) {
        num++;
        hits_counter += cache.cache_elem(new_elem);
    }
    cache.clear();

    std::cout << "number of strikes = " << hits_counter << '\n';
    uint64_t result = (double) hits_counter / (double) num * 100;
    std::cout << result << "% \n";   

    run_tests(); 
}