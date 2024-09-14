#include <iostream>
#include <vector>
#include <cstdint>

#include "tests.hpp"
#include "cache.hpp"

struct Test {
    uint64_t    cache_size;
    vector<int> elements;
    uint64_t    hits_num;
};

void do_tests () {

    Cache_class<int> cache;

    Test tests[] = {{10, {1, 2, 4, 5, 7, 8, 9}, 0}};

    const int TESTS_NUM = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < TESTS_NUM; ++i) {
        cache.create_cache(tests[i].cache_size);
        uint64_t hits_counter = 0;

        for (auto elem: tests[i].elements) {
            hits_counter += cache.cache_elem(elem);
        }
        if (hits_counter != tests[i].hits_num) {
            std::cout << "test [" << i + 1<< "] wrong\n";
            std::cout << "test hits value = " << tests[i].hits_num 
                      << "\ncurrent value = " << hits_counter << '\n';
        }
        else 
            std::cout << "test [" << i + 1 << "] Ok\n";

    }
}