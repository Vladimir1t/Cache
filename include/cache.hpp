#ifndef CACHE_H
#define CACHE_H

#include <iostream>
#include <cstdint>
#include <cassert>
#include <unordered_map>
#include <list>

namespace Cache {

/** @brief Cache - a class with its strucures and methods of 2Q cache
 */
template <typename T>
class Cache_2Q {

public: 

    Cache_2Q(uint64_t cache_size) : Main_q {cache_size / 5 + 1}, 
                                    Out_q  {cache_size - Main_q.size} {}

    ~Cache_2Q() {}

private:

    enum Queue_t {
        MAIN_Q,
        OUT_Q
    };

    using list_it = typename std::list<T>::iterator;
   
    struct Elem_hash_t {
        list_it value;   
        Queue_t num_queue;
    };

    struct Queue {
        uint64_t     size;
        std::list<T> list_q;
    };

    Queue Main_q;
    Queue Out_q;

    uint64_t size_hash_t = 0;

    std::unordered_map<T, Elem_hash_t> hash_t;

    bool find_in_cache(const T& elem) {
        Elem_hash_t get_elem = hash_t.at(elem);
        
        if (get_elem.num_queue == MAIN_Q) {     
                       
            T new_elem = *(get_elem.value);     
            Main_q.list_q.push_front(new_elem);

            Main_q.list_q.erase(get_elem.value);
            hash_t.erase(*(get_elem.value));

            hash_t.insert({new_elem, {Main_q.list_q.begin(), MAIN_Q}});

            #ifdef Debug
                std::cout << "Hit in Main_q" << std::endl;
            #endif

            return 1;
        }
        else if (get_elem.num_queue == OUT_Q) { 

            Main_q.list_q.push_front(*(get_elem.value));

            if (Main_q.size < Main_q.list_q.size()) {            // if Main_q size is above the threshold
                T eresed_elem = Main_q.list_q.back();
                Main_q.list_q.pop_back();

                auto get_elem_erased {hash_t.find(eresed_elem)};
                get_elem.num_queue = OUT_Q;                      // Main_q -> Out_q
                
                Out_q.list_q.push_front(eresed_elem);
            }
            
            Out_q.list_q.erase(get_elem.value);
            get_elem.num_queue = MAIN_Q;                          // Out_q -> Main_q
            get_elem.value = Main_q.list_q.begin();
                
            #ifdef Debug
                std::cout << "Hit in Out_q" << std::endl;
            #endif

            return 1;
        }
        return 0;
    }

    void erase_cache(Queue& queue) {

        hash_t.erase(queue.list_q.back());
        queue.list_q.pop_back();
    }

public:

    void create_cache(uint64_t cache_size) {

        Main_q.size = cache_size * 0.2 + 1;       // MAIN ~ 20%
        Out_q.size  = cache_size - Main_q.size;   // OUT  ~ 80%

        hash_t.reserve(cache_size);
        #ifdef Debug
            std::cout << Main_q.size << ' ' << Out_q.size << std::endl;
        #endif
    }
    /** @brief cache_elem() - function that cache the element by algorithm 2Q
     *  @param elem element that is cached
     *  @return 0 or 1 
     */
    bool cache_elem(const T& elem) {
        #ifdef Debug
            std::cout << "value = " << elem << std::endl;
        #endif

        if (hash_t.find(elem) == hash_t.end()) {     // doesn't locate in cache

            if (Main_q.size > Main_q.list_q.size()) { 
                Main_q.list_q.push_back(elem);

                #ifdef Debug
                    std::cout << "put in list Main_q {" << Main_q.list_q.back() << "}\n\n";
                #endif

                Elem_hash_t elem_hash_t = {--Main_q.list_q.end(), MAIN_Q};
               
                hash_t.insert({elem, elem_hash_t});

                return 0;
            }
            else if (Out_q.size > Out_q.list_q.size()) {
                Out_q.list_q.push_back(elem);

                #ifdef Debug
                    std::cout << "put in list Out_q {" << Out_q.list_q.back() << "}\n\n";
                #endif 

                hash_t.insert({elem, {--Out_q.list_q.end(), OUT_Q}});  
                return 0;
            }
            else if (Out_q.size == Out_q.list_q.size() && Out_q.size != 0){ 
                erase_cache(Out_q);

                Out_q.list_q.push_front(elem);

                #ifdef Debug
                    std::cout << "put in list Out_q {" << Out_q.list_q.front() << "}\n\n";
                #endif

                hash_t.insert({elem, {Out_q.list_q.begin(), OUT_Q}});   

                return 0;
            }
            else {
                erase_cache(Main_q);

                Main_q.list_q.push_front(elem);

                #ifdef Debug
                    std::cout << "put in list Main_q {" << Main_q.list_q.front() << "}\n\n";
                #endif 

                hash_t.insert({elem, {Main_q.list_q.begin(), MAIN_Q}});    

                return 0;
            }
        }
        else {   // locate in cache
            return find_in_cache(elem);
        }
    }
    // void clear() { 
    //     Main_q.list_q.clear();
    //     Main_q.size = 0;
    //     Out_q.list_q.clear();
    //     Out_q.size = 0;
    //     hash_t.clear();
    // }
};
}

#endif // CACHE_H