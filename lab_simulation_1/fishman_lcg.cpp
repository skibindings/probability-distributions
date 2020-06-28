#include "pch.h"
#include "fishman_lcg.h"
#include<iostream>

long double FishmanLCG::getNextRandomNumber() {
    seed_ = (kMultiplier*seed_ + kIncrement) % kModulus;
    return seed_ / (long double)kModulus;
}


unsigned int FishmanLCG::getNextRandomNumber(unsigned long long seed) {
    return (kMultiplier*seed + kIncrement) % kModulus;
}


unsigned int FishmanLCG::getNextRandomNumber(unsigned long long seed, unsigned int steps) {
    for (int i = 0; i < steps; i++) {
        seed = (kMultiplier*seed + kIncrement) % kModulus;
    }
    return seed;
}


unsigned int FishmanLCG::uniform_number(unsigned int number, unsigned int d) {
    return (number / (long double)kModulus) * d;
}

double FishmanLCG::uniform_number(unsigned int number) {
    return number / (long double)kModulus;
}
 
void FishmanLCG::setSeed(unsigned long long new_seed) {
    seed_ = new_seed % kModulus;
}


unsigned long FishmanLCG::getInitialSeed() {
    return kInitialSeed;
}

unsigned int FishmanLCG::getModulus() {
    return kModulus;
}