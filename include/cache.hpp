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

    //template <typename T>
    std::unordered_map<T, Elem_hash_t> hash_t;


    void erase_elem() {

    }

public:

    void create_cache() {
        std::cout << "Input the size of cache\n";
        uint64_t size = 0;
        cin >> size;

        Am.size_In  = size * 0.2 + 1;    // IN  ~ 20%
        A1.size_Out = size - Am.size_In; // OUT ~ 80%
        //size_hash_t = size;
        hash_t.reserve(size);

        cout << Am.size_In << ' ' << A1.size_Out << '\n';
    }

    int insert_elem(T elem) {
        std::cout << "elem = " << elem << '\n';

        if (hash_t.find(elem) == hash_t.end()) { 
            //printf ("ok\n");
            if (Am.size_In > Am.list_In.size()) { 
                Am.list_In.push_front(elem);
                cout << "put in list Am {" << Am.list_In.front() << "}\n";

                Elem_hash_t elem_hash_t = {elem, 0}; 
                hash_t.insert({elem, elem_hash_t});
            }
            else if (A1.size_Out > A1.list_Out.size()) {
                A1.list_Out.push_front(elem);
                cout << "put in list A1 {" << A1.list_Out.front() << "}\n";

                Elem_hash_t elem_hash_t = {elem, 1}; 
                hash_t.insert({elem, elem_hash_t});
            }
            else { // удалить конец A1 
                hash_t.erase(A1.list_Out.back());
                A1.list_Out.pop_back();
                cout << "put in list A1 {" << A1.list_Out.back() << "}\n";

                A1.list_Out.push_back(elem);
                Elem_hash_t elem_hash_t = {elem, 1}; 
                hash_t.insert({elem, elem_hash_t});
            }
        }
        else {                                        // locate in cache
            auto get_elem {hash_t.find(elem)};
            //printf ("ok\n");
            //std::list<T>::iterator it;

            if (get_elem->second.num_queue == 0) { // Am
                cout << "Strike in Am\n";

                auto it {Am.list_In.begin()};
                for (; it != Am.list_In.end(); it++)
                    if (*it == elem) {
                        Am.list_In.push_front(*it);
                        Am.list_In.erase(it);
                        break;
                    };
            }
            else if (get_elem->second.num_queue == 1) {  // A1

                auto it {A1.list_Out.begin()};
                for (; it != A1.list_Out.end(); it++)
                    if (*it == elem) {
                        Am.list_In.push_front(*it);
                        if (Am.size_In > Am.list_In.size()) {

                            
                            Elem_hash_t elem_hash_t = {elem, 1}; 
                            hash_t.insert({elem, elem_hash_t});
                        }
                        A1.list_Out.erase(it);
                        break;
                    };
                //Am.list_In.push_front(get_elem);
                cout << "Strike in A1\n";

                Elem_hash_t elem_hash_t = {elem, 1}; 
                hash_t.insert({elem, elem_hash_t});
            }
        }
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