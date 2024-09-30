#include <iostream>
#include <random>
#include <cstdint>
#include <limits>

int main() {

    std::random_device rd;
    std::mt19937 generator(rd());
    std::poisson_distribution<> distributor(50);

    uint64_t amount = 10'000'000;
    
    std::cout << amount << ' ';
    for (uint64_t id = 0; id < amount; ++id) {
        std::cout << distributor(generator) << ' ';
    }
    std::cout << '\n';

    return 0;
}   