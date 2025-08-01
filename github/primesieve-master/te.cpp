#include <iostream>
#include <primesieve.hpp>


int main() {
    primesieve::iterator it;
    uint64_t prime = it.next_prime();

    // Iterate over the primes < 10^6
    for (; prime < 1000000; prime = it.next_prime()) std::cout << prime << std::endl;

    return 0;
}