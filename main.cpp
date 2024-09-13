#include <iostream>

#include "cache.hpp"

int main()
{
    Cache_class<int> cache;
    cache.create_cache();

    uint64_t new_elem = 0;
    while ((std::cin >> new_elem))
        cache.insert_elem(new_elem);


}