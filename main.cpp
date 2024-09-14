#include <iostream>

#include "cache.hpp"

int main()
{
    Cache_class<int> cache;
    cache.create_cache();

    std::cout << "input elements\n";

    uint64_t new_elem = 0;
    uint64_t strike_counter = 0, num = 0;
    while ((std::cin >> new_elem) && !isalpha(new_elem)) {
        num++;
        strike_counter += cache.insert_elem(new_elem);
    }

    std::cout << "number of strikes = " << strike_counter << '\n';
    std::cout << strike_counter / num * 100<< '% \n';    
}