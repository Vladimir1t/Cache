#ifndef CACHE_H
#define CACHE_H

#include <iostream>
#include <cstdint>
#include <cassert>
#include <unordered_map>
#include <list>

using namespace std;

/** @brief Cache - a class with its strucures and methods of 2Q cache
 * 
 */
//namespace Pr {

template <typename T>
class Cache_class {

private:
    // uint64_t cache_size_In = 0;
    // uint64_t cache_size_A1 = 0;

    struct Elem_hash_t {
        T        value;
        uint32_t num_queue;
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

    uint64_t size_hash_t = 0;

    std::unordered_map<T, Elem_hash_t> hash_t;

    void erase_elem() {

    }

    uint32_t find_in_cache(T elem) {
        auto get_elem {hash_t.find(elem)};
        
        if (get_elem->second.num_queue == 0) {     // Am

            auto it {Am.list_In.begin()};
            for (; it != Am.list_In.end(); ++it)
                if (*it == elem) {
                    Am.list_In.push_front(*it);
                    Am.list_In.erase(it);
                    break;
                }
            cout << "Hit in Am\n";

            return 1;
        }
        else if (get_elem->second.num_queue == 1) {  // A1

            auto it {A1.list_Out.begin()};
            for (; it != A1.list_Out.end(); ++it)
                if (*it == elem) {
                    Am.list_In.push_front(*it);

                    if (Am.size_In < Am.list_In.size()) { // if Am size is above the threshold
                        T eresed_elem = Am.list_In.back();
                        Am.list_In.pop_back();

                        auto get_elem_erased {hash_t.find(eresed_elem)};
                        get_elem->second.num_queue = 1;                      // Am -> A1
                        
                        A1.list_Out.push_front(eresed_elem);
                    }
                    
                    get_elem->second.num_queue = 0;                          // A1 -> Am
                    A1.list_Out.erase(it);
                    break;
                }
           
            cout << "Hit in A1\n";

            return 1;
        }

        return 0;
    }

public:

    void create_cache(uint64_t cache_size) {

        Am.size_In  = cache_size * 0.2 + 1;    // IN  ~ 20%
        A1.size_Out = cache_size - Am.size_In; // OUT ~ 80%

        hash_t.reserve(cache_size);

        cout << Am.size_In << ' ' << A1.size_Out << '\n';
    }
    /** @brief cache_elem - function that cache the element by algorith 2Q
     *  @param elem element 
     *  @return 0 or 1 
     */
    uint32_t cache_elem(T elem) {
        std::cout << "value = " << elem << '\n';

        if (hash_t.find(elem) == hash_t.end()) { 

            if (Am.size_In > Am.list_In.size()) { 
                Am.list_In.push_front(elem);
                cout << "put in list Am {" << Am.list_In.front() << "}\n\n";

                Elem_hash_t elem_hash_t = {elem, 0}; 
                hash_t.insert({elem, elem_hash_t});

                return 0;
            }
            else if (A1.size_Out > A1.list_Out.size()) {
                A1.list_Out.push_front(elem);
                cout << "put in list A1 {" << A1.list_Out.front() << "}\n\n";

                Elem_hash_t elem_hash_t = {elem, 1}; 
                hash_t.insert({elem, elem_hash_t});

                return 0;
            }
            else { 
                hash_t.erase(A1.list_Out.back());
                A1.list_Out.pop_back();
                cout << "put in list A1 {" << A1.list_Out.back() << "}\n\n";

                A1.list_Out.push_front(elem);
                Elem_hash_t elem_hash_t = {elem, 1}; 
                hash_t.insert({elem, elem_hash_t});

                return 0;
            }
        }
        else {                              // locate in cache
            return find_in_cache(elem);
        }
    }


    template <typename U>
    void put_in_cache(T elem, U key) {
        Am.list_In.push_front(elem);

    }
};


#endif // CACHE_H