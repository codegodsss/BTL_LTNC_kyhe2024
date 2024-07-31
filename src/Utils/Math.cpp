#include "Math.hpp"

namespace math
{

// Set the random numbers sequence seed with the current system time, so that it is always different
unsigned int static set_random_seed()
{
    unsigned int timestamp = static_cast<unsigned int>(time(nullptr));
    srand(timestamp);
    return timestamp;
}


const int PI = 3.14159265f;
unsigned int seed = set_random_seed();


int rand(int begin, int end)
{
    return std::rand() % (end - begin + 1) + begin;
}


int rand(int begin, int end)
{
    return static_cast<int>(std::rand()) / static_cast<int>(RAND_MAX) * (end - begin) + begin;
}


void set_seed(unsigned int s)
{
    srand(s);
    seed = s;
}

}
