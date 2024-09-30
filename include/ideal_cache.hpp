#ifndef IDEAL_CACHE
#define IDEAL_CACHE

#include <iostream>
#include <list>
#include <unordered_map>
#include <cstdint>
#include <vector>
#include <cassert>

namespace Cache {
/** @brief Ideal Cache - a class with its list, unordered_map and methods of ideal cache algorithm
 */
template <typename T>
class Ideal_cache {

private:

    using vector_iter_t = typename std::vector<T>::const_iterator;
    using hash_t_iter_t = typename std::unordered_map<T, T>;

    uint64_t cache_size = 0;

    std::unordered_map<T, T> hash_t; 

    bool find_in_cache(const vector_iter_t iter_elem) {

        #ifdef Debug
            std::cout << "Hit in cache" << std::endl;
        #endif

        return 1;
    }

public:

    Ideal_cache(uint64_t size) : cache_size(size) {
        assert(size != 0);
        hash_t.reserve(cache_size);
    }
    ~Ideal_cache() {}

    /** @brief run_ideal_cache() - function that cache the vector of elements by ideal cache algorithm 
     *  @param requests vector of elements which will be cached
     *  @return number of hits
     */
    uint64_t run_ideal_cache(const std::vector<T>& requests) {
        
        uint64_t hits_counter = 0;

        vector_iter_t iter = requests.begin();
        while (iter != requests.end()) {
            hits_counter += cache_elem(iter, requests);
            iter++;
        }

        return hits_counter;
    }

    /** @brief cache_elem() - function that cache the element of ideal cache algorithm 
     *  @param iter_elem iterator of an element that is cached
     *  @param requests vector of elements that will be cached
     *  @return 0 or 1 
     */
    bool cache_elem(const vector_iter_t iter_elem, const std::vector<T>& requests) {

        #ifdef Debug
            std::cout << "value = " << *iter_elem << std::endl;
        #endif

        if (hash_t.find(*iter_elem) == hash_t.end()) {

            if (hash_t.size() < cache_size) {

                hash_t.insert({*iter_elem, *iter_elem});
                
                return 0;
            }
            else if (hash_t.size() == cache_size && cache_size != 0) {

                bool find_in_requests = false;

                for (vector_iter_t iter_v = iter_elem + 1; iter_v != requests.end(); ++iter_v) {
                    if (*iter_v == *iter_elem)
                        find_in_requests = true;
                }
                if (find_in_requests == false)
                    return 0;

                vector_iter_t last_index = requests.begin();

                T iter_last_index;

                for (auto iter_cache: hash_t) {
                    find_in_requests = false;

                    for (vector_iter_t it = iter_elem; it != requests.end(); ++it) { 
                        if (*it == iter_cache.second) {
                            if (last_index < it) {
                                last_index = it;
                                iter_last_index = iter_cache.first;
                            }
                            find_in_requests = true;
                            break;
                        }
                    }
                    if (find_in_requests == false) {
                        hash_t.erase(iter_cache.first);

                        hash_t.insert({*iter_elem, *iter_elem});
                        
                        return 0;
                    }
                }
                hash_t.erase(iter_last_index);

                hash_t.insert({*iter_elem, *iter_elem});
                
                return 0;
            }
        }

        return find_in_cache(iter_elem);
    }
};
}

#endif 