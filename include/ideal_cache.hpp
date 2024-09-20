#ifndef IDEAL_CACHE
#define IDEAL_CACHE

#include <iostream>
#include <list>
#include <unordered_map>
#include <cstdint>
#include <vector>

#define ERROR -1

/** @brief Ideal Cache - a class with its list, unordered_map and methods of ideal cache algorithm
 */
template <typename T>
class Ideal_cache {

private:

    using list_iter_t   = typename std::list<T>::iterator;
    using vector_iter_t = typename std::vector<T>::iterator;

    std::list<T> list_cache;

    uint64_t cache_size = 0;

    std::unordered_map<T, list_iter_t> hash_t;

    uint32_t find_in_cache(vector_iter_t iter_elem) {

        #ifdef Debug
            std::cout << "Hit in cache" << std::endl;
        #endif

        return 1;
    }

public:

    void create_cache(uint64_t size) {

        cache_size = size;
        hash_t.reserve(cache_size);

        #ifdef Debug
            std::cout << "ideal cache size " << cache_size << std::endl;
        #endif
    }

    /** @brief run_ideal_cache() - function that cache the vector of elements by ideal cache algorithm 
     *  @param requests vector of elements which will be cached
     *  @return number of hits
     */
    uint64_t run_ideal_cache(std::vector<T>& requests) {
        
        uint64_t hits_counter = 0;

        auto iter = requests.begin();
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
    uint32_t cache_elem(vector_iter_t iter_elem, std::vector<T>& requests) {

        #ifdef Debug
            std::cout << "value = " << *iter_elem << std::endl;
        #endif

        if (hash_t.find(*iter_elem) == hash_t.end()) {

            if (list_cache.size() < cache_size) {

                list_cache.push_front(*iter_elem);
                hash_t.insert({*iter_elem, list_cache.begin()});
                
                return 0;
            }
            else if (list_cache.size() == cache_size && cache_size != 0) {

                bool find_in_requests = false;

                for (vector_iter_t iter_v = iter_elem + 1; iter_v != requests.end(); ++iter_v) {
                    if (*iter_v == *iter_elem)
                        find_in_requests = true;
                }
                if (find_in_requests == false)
                    return 0;

                vector_iter_t last_index      = requests.begin();
                list_iter_t   iter_last_index = list_cache.begin();

                for (list_iter_t iter_cache = list_cache.begin(); iter_cache != list_cache.end(); ++iter_cache) {
                    find_in_requests = false;

                    for (vector_iter_t it = iter_elem; it != requests.end(); ++it) { 
                        if (*it == *iter_cache) {
                            if (last_index < it) {
                                last_index = it;
                                iter_last_index = iter_cache;
                            }
                            find_in_requests = true;
                            break;
                        }
                    }
                    if (find_in_requests == false) {
                        hash_t.erase(*iter_cache);
                        list_cache.erase(iter_cache);

                        list_cache.push_front(*iter_elem);
                        hash_t.insert({*iter_elem, list_cache.begin()});
                        
                        return 0;
                    }
                }
                hash_t.erase(*iter_last_index);
                list_cache.erase(iter_last_index);

                list_cache.push_front(*iter_elem);
                hash_t.insert({*iter_elem, list_cache.begin()});
                
                return 0;
            }
            else 
                return ERROR;
        }
        else {
            return find_in_cache(iter_elem);
        }
    }
    void clear(){

        list_cache.clear();

        cache_size = 0;

        hash_t.clear();
    }
};

#endif 