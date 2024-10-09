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

    Cache_2Q(uint64_t cache_size) : Main_q_ {cache_size / 5 + 1}, 
                                    Out_q_  {cache_size - Main_q_.size_} {}

private:

    enum class Queue_t {
        MAIN_Q,
        OUT_Q  
    };

    using list_it = typename std::list<T>::iterator;
   
    struct Elem_hash_t_ {
        list_it value_;   
        Queue_t num_queue_;
    };

    struct Queue {
        uint64_t     size_;
        std::list<T> list_q_;
    };

    Queue Main_q_;
    Queue Out_q_;

    std::unordered_map<T, Elem_hash_t_> hash_t_;

    bool find_in_cache(const T& elem) {

        Elem_hash_t_ get_elem = hash_t_.at(elem);
        
        if (get_elem.num_queue_ == Queue_t::MAIN_Q) {     
                       
            T new_elem = *(get_elem.value_);     
            Main_q_.list_q_.push_front(new_elem);

            Main_q_.list_q_.erase(get_elem.value_);
            hash_t_.erase(*(get_elem.value_));

            hash_t_.insert({new_elem, {Main_q_.list_q_.begin(), Queue_t::MAIN_Q}});

            #ifndef NDEBUG
                std::cout << "Hit in Main_q" << std::endl;
            #endif

            return true;
        }
        else if (get_elem.num_queue_ == Queue_t::OUT_Q) { 

            Main_q_.list_q_.push_front(*(get_elem.value_));

            if (Main_q_.size_ < Main_q_.list_q_.size()) {         // if Main_q size is above the threshold
                T eresed_elem = Main_q_.list_q_.back();
                Main_q_.list_q_.pop_back();

                auto get_elem_erased {hash_t_.find(eresed_elem)};
                get_elem.num_queue_ = Queue_t::OUT_Q;                   // Main_q -> Out_q
                
                Out_q_.list_q_.push_front(eresed_elem);
            }
            
            Out_q_.list_q_.erase(get_elem.value_);
            get_elem.num_queue_ = Queue_t::MAIN_Q;                      // Out_q -> Main_q
            get_elem.value_ = Main_q_.list_q_.begin();
                
            #ifndef NDEBUG
                std::cout << "Hit in Out_q_" << std::endl;
            #endif

            return true;
        }
        return false;
    }

    void erase_cache(Queue& queue) {

        hash_t_.erase(queue.list_q_.back());
        queue.list_q_.pop_back();
    }

    void put_in_queue(Queue& queue, const T& elem, Queue_t queue_t) {
       
        queue.list_q_.push_back(elem);
        #ifndef NDEBUG
            std::cout << "put in list {" << (int)queue_t << '} ' << queue.list_q_.back() << "}\n\n";
        #endif
        Elem_hash_t_ elem_hash_t = {--queue.list_q_.end(), queue_t};
               
        hash_t_.insert({elem, elem_hash_t});
    }

public:

    /** @brief cache_elem() - function that cache the element by algorithm 2Q
     *  @param elem element that is cached
     *  @return 0 or 1 
     */
    bool cache_elem(const T& elem) {
        #ifndef NDEBUG
            std::cout << "value = " << elem << std::endl;
        #endif

        if (hash_t_.find(elem) == hash_t_.end()) {     // doesn't locate in cache

            if (Main_q_.size_ > Main_q_.list_q_.size()) { 
                put_in_queue(Main_q_, elem, Queue_t::MAIN_Q);

                return 0;
            }
            else if (Out_q_.size_ > Out_q_.list_q_.size()) {
                put_in_queue(Out_q_, elem, Queue_t::OUT_Q);
                
                return 0;
            }
            else if (Out_q_.size_ == Out_q_.list_q_.size() && Out_q_.size_ != 0){ 
                erase_cache(Out_q_);
               
                Out_q_.list_q_.push_front(elem);
                #ifndef NDEBUG
                    std::cout << "put in list Out_q_ {" << Out_q_.list_q_.front() << "}\n\n";
                #endif
                hash_t_.insert({elem, {Out_q_.list_q_.begin(), Queue_t::OUT_Q}});   

                return 0;
            }
            else {
                erase_cache(Main_q_);

                Main_q_.list_q_.push_front(elem);
                #ifndef NDEBUG
                    std::cout << "put in list Main_q_ {" << Main_q_.list_q_.front() << "}\n\n";
                #endif 
                hash_t_.insert({elem, {Main_q_.list_q_.begin(), Queue_t::MAIN_Q}});    

                return 0;
            }
        }
        else {                                 // locate in cache
            return find_in_cache(elem);
        }
    }
};
}

#endif // CACHE_H