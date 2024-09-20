#ifndef CACHE_H
#define CACHE_H

#include <iostream>
#include <cstdint>
#include <cassert>
#include <unordered_map>
#include <list>

#define MAIN_Q 0
#define OUT_Q  1

/** @brief Cache - a class with its strucures and methods of 2Q cache
 */
template <typename T>
class Cache_2Q {

private:

    using list_it = typename std::list<T>::iterator;
   
    struct Elem_hash_t {
        list_it  value;   
        uint32_t num_queue;
    };

    struct In_queue {
        uint64_t     size_M;
        std::list<T> list_In;
    };

    struct Out_queue {
        uint64_t     size_Out;
        std::list<T> list_Out;
    };

    In_queue  Main_q = {0};
    Out_queue Out_q  = {0};

    uint64_t size_hash_t = 0;

    std::unordered_map<T, Elem_hash_t> hash_t;

    uint32_t find_in_cache(const T& elem) {
        Elem_hash_t get_elem = hash_t.at(elem);
        
        if (get_elem.num_queue == MAIN_Q) {     
                       
            T new_elem = *(get_elem.value);     
            Main_q.list_In.push_front(new_elem);

            Main_q.list_In.erase(get_elem.value);
            hash_t.erase(*(get_elem.value));

            hash_t.insert({new_elem, {Main_q.list_In.begin(), MAIN_Q}});

            #ifdef Debug
                std::cout << "Hit in Main_q" << std::endl;
            #endif

            return 1;
        }
        else if (get_elem.num_queue == OUT_Q) { 

            Main_q.list_In.push_front(*(get_elem.value));

            if (Main_q.size_M < Main_q.list_In.size()) { // if Main_q size is above the threshold
                T eresed_elem = Main_q.list_In.back();
                Main_q.list_In.pop_back();

                auto get_elem_erased {hash_t.find(eresed_elem)};
                get_elem.num_queue = OUT_Q;                      // Main_q -> Out_q
                
                Out_q.list_Out.push_front(eresed_elem);
            }
            
            Out_q.list_Out.erase(get_elem.value);
            get_elem.num_queue = MAIN_Q;                          // Out_q -> Main_q
            get_elem.value = Main_q.list_In.begin();
                
            #ifdef Debug
                std::cout << "Hit in Out_q" << std::endl;
            #endif

            return 1;
        }
        return 0;
    }

public:

    void create_cache(uint64_t cache_size) {

        Main_q.size_M  = cache_size * 0.2 + 1;       // MAIN ~ 20%
        Out_q.size_Out = cache_size - Main_q.size_M; // OUT  ~ 80%

        hash_t.reserve(cache_size);
        #ifdef Debug
            std::cout << Main_q.size_M << ' ' << Out_q.size_Out << std::endl;
        #endif
    }
    /** @brief cache_elem() - function that cache the element by algorithm 2Q
     *  @param elem element that is cached
     *  @return 0 or 1 
     */
    uint32_t cache_elem(const T& elem) {
        #ifdef Debug
            std::cout << "value = " << elem << std::endl;
        #endif

        if (hash_t.find(elem) == hash_t.end()) {     // doesn't locate in cache

            if (Main_q.size_M > Main_q.list_In.size()) { 
                Main_q.list_In.push_back(elem);

                #ifdef Debug
                    std::cout << "put in list Main_q {" << Main_q.list_In.back() << "}\n\n";
                #endif

                Elem_hash_t elem_hash_t = {--Main_q.list_In.end(), MAIN_Q};
               
                hash_t.insert({elem, elem_hash_t});

                return 0;
            }
            else if (Out_q.size_Out > Out_q.list_Out.size()) {
                Out_q.list_Out.push_back(elem);

                #ifdef Debug
                    std::cout << "put in list Out_q {" << Out_q.list_Out.back() << "}\n\n";
                #endif 

                hash_t.insert({elem, {--Out_q.list_Out.end(), OUT_Q}});  // добавляем итератор

                return 0;
            }
            else if (Out_q.size_Out == Out_q.list_Out.size() && Out_q.size_Out != 0){ 
                hash_t.erase(Out_q.list_Out.back());
                Out_q.list_Out.pop_back();

                Out_q.list_Out.push_front(elem);

                #ifdef Debug
                    std::cout << "put in list Out_q {" << Out_q.list_Out.front() << "}\n\n";
                #endif

                hash_t.insert({elem, {Out_q.list_Out.begin(), OUT_Q}});   

                return 0;
            }
            else {
                hash_t.erase(Main_q.list_In.back());
                Main_q.list_In.pop_back();

                Main_q.list_In.push_front(elem);

                #ifdef Debug
                    std::cout << "put in list Main_q {" << Main_q.list_In.front() << "}\n\n";
                #endif 

                hash_t.insert({elem, {Main_q.list_In.begin(), MAIN_Q}});    

                return 0;
            }
        }
        else {   // locate in cache
            return find_in_cache(elem);
        }
    }
    void clear() { 

        Main_q.list_In.clear();
        Main_q.size_M = 0;

        Out_q.list_Out.clear();
        Out_q.size_Out = 0;

        hash_t.clear();
    }
};

#endif // CACHE_H