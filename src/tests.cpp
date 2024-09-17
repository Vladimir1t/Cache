#include <iostream>
#include <vector>
#include <cstdint>

#include "tests.hpp"
#include "cache.hpp"
#include "ideal_cache.hpp"

#define Ideal_cache

struct Test {
    uint64_t         cache_size;
    std::vector<int> elements;
    uint64_t         hits_num;
};

int main() {
    Cache_class<int> cache;

    uint64_t correct_test_count = 0;

    Test tests[] = {{10, {1, 2, 4, 5, 7, 8, 9}, 0},
                    {10, {1, 1, 1, 2, 2, 2, 2, 3}, 5},
                    {7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 5, 8}, 3},
                    {7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 5, 4, 8, 3, 10}, 4},
                    {7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 5, 4, 8, 3, 9}, 3},
                    {5, {1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1}, 9},
                    {5, {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2}, 2},
                    {5, {1, 2, 3, 4, 5, 6, 7, 5, 34, 8, 10, 2}, 1},
                    {1, {1, 1, 1, 1, 1}, 4},
                    {1, {1, 2, 3, 3, 2}, 1}};

    const int TESTS_NUM = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < TESTS_NUM; ++i) {
        cache.create_cache(tests[i].cache_size);
        uint64_t hits_counter = 0;

        for (int elem: tests[i].elements) {
            hits_counter += cache.cache_elem(elem);
        }
        if (hits_counter != tests[i].hits_num) {
            std::cout << "test [" << i + 1 << "] wrong\n";
            std::cout << "expected hits value = " << tests[i].hits_num 
                      << "\ncurrent value = " << hits_counter << '\n';
        }
        else 
            correct_test_count++;

        cache.clear();
    }
    if (correct_test_count == TESTS_NUM)
        std::cout << "--- All tests are correct ---\n";

    #ifdef Ideal_cache                      // compare 2Q with ideal (perfect) cache algorithm
        Ideal_cache_class<int> ideal_cache;

        for (int i = 0; i < TESTS_NUM; ++i) {

            uint64_t cache_size   = 0;
            uint64_t hits_counter = 0;

            #ifdef Debug
                std::cout << "Input the size of ideal cache\n";
            #endif
                std::cin >> cache_size;
            #ifdef Debug
                std::cout << cache_size << '\n';
            #endif
            ideal_cache.create_cache(cache_size);

            // for (auto elem_it {tests[i].elements.begin()}; elem_it != tests[i].elements.end(); ++elem_it) {

            //     hits_counter += ideal_cache.cache_elem(elem_it, tests[i].elements);
            // }
            hits_counter = ideal_cache.run_ideal_cache(tests[i].elements);
            std::cout << "hits "<< hits_counter << '\n';
            ideal_cache.clear();
        }
    #endif
}