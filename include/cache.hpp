#ifndef CACHE_H
#define CACHE_H

#include <iostream>
#include <cstdint>
#include <unordered_map>
#include <list>

/** @brief Cache - class with its strucures and methods of 2Q cache
 * 
 */
//namespace Pr {

template <typename T>
class Cache_class {

private:
    // uint64_t cache_size_In = 0;
    // uint64_t cache_size_A1 = 0;

    struct Elem_hash_t {
        uint64_t value;
        uint64_t num_queue;
    };

    struct In_queue {
        uint64_t     size_In;
        std::list<T> list_In;
    };

    struct Out_queue {
        uint64_t     size_Out;
        std::list<T> list_Out;
    };

    In_queue  Am = {0};
    Out_queue A1 = {0};

    //template <typename T>
    std::unordered_map<T, Elem_hash_t> hash_t;


    void erase_elem() {

    }

public:

    void create_cache() {
        std::cout << "input the size of cache\n";
        uint64_t size = 0;
        std::cin >> size;
        Am.size_In  = size * 0.2; // IN
        A1.size_Out = size * 0.8; // OUT
    }

    void insert_elem(T elem) {
        std::cout << "ok" << elem << '\n';
    }

    void find_in_cache() {
        // find in hash_table In or Out
        // move in list
    }

    template <typename U>
    void put_in_cache(T elem, U key) {
        Am.list_In.push_front(elem);

    }

};


#endif // CACHE_H