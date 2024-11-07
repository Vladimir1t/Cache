#ifndef IDEAL_CACHE
#define IDEAL_CACHE

#include <iostream>
#include <unordered_map>
#include <cstdint>
#include <vector>
#include <cassert>
#include <algorithm>

namespace Cache {
/** @brief Ideal Cache - a class with its unordered_map and methods of ideal cache algorithm
 */
template <typename T>
class Ideal_cache {

private:

    using vector_iter_t = typename std::vector<T>::const_iterator;

    uint64_t cache_size_ = 0;

    std::unordered_map<T, T> hash_t_; 

    bool find_in_cache(const vector_iter_t iter_elem) {

        #ifndef NDEBUG
            std::cout << "Hit in cache" << std::endl;
        #endif

        return true;
    }

public:

    Ideal_cache(uint64_t size) : cache_size_(size) {
        assert(size != 0);
        hash_t_.reserve(cache_size_);
    }

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
     *  @return true or false 
     */
    bool cache_elem(const vector_iter_t iter_elem, const std::vector<T>& requests) {

        #ifndef NDEBUG
            std::cout << "value = " << *iter_elem << std::endl;
        #endif

        if (hash_t_.find(*iter_elem) == hash_t_.end()) {

            if (hash_t_.size() < cache_size_) {

                hash_t_.insert({*iter_elem, *iter_elem});
                
                return false;
            }
            else if (hash_t_.size() == cache_size_ && cache_size_ != 0) {

                bool find_in_requests = false;

                for (vector_iter_t iter_v = iter_elem + 1; iter_v != requests.end(); ++iter_v) {
                    if (*iter_v == *iter_elem)
                        find_in_requests = true;
                }
                if (find_in_requests == false)
                    return false;

                vector_iter_t last_index = requests.begin();

                T iter_last_index;

                for (auto iter_cache: hash_t_) {
                    find_in_requests = false;

                    vector_iter_t it = std::find(iter_elem, requests.end(), iter_cache.second);
                    if (it != requests.end()) {
                        if (last_index < it) {
                            last_index = it;
                            iter_last_index = iter_cache.first;
                        }
                    }
                    else {
                        hash_t_.erase(iter_cache.first);

                        hash_t_.insert({*iter_elem, *iter_elem});
                        
                        return false;
                    }
                }
                hash_t_.erase(iter_last_index);

                hash_t_.insert({*iter_elem, *iter_elem});
                
                return false;
            }
        }

        return find_in_cache(iter_elem);
    }
};
}

#endif 