#pragma once
#include <math.h>

class FishmanLCG
{
public:
    FishmanLCG() = default;

    long double getNextRandomNumber();
    unsigned int getNextRandomNumber(unsigned long long seed);
    unsigned int getNextRandomNumber(unsigned long long seed, unsigned int steps);

    void setSeed(unsigned long long new_seed);
    unsigned long getInitialSeed();

    unsigned int uniform_number(unsigned int number, unsigned int d);
    double uniform_number(unsigned int number);

    unsigned int getModulus();

private:
    const unsigned long long kModulus{ (unsigned long long)pow(2,31) - 1 };
    const unsigned long long kMultiplier{ 742938285 }; //1226874159
    const unsigned long long kIncrement{ 0 };
    const unsigned long long kInitialSeed{ 1 };
   
    unsigned long long seed_{ kInitialSeed };
};

