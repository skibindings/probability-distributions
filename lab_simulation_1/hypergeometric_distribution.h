#pragma once
#include "probability_distribution.h"

namespace disrtibutions {

    class HypergeometricDistribution : public ProbabilityDistribution
    {
    public:
        HypergeometricDistribution(unsigned int N, unsigned int D, unsigned int n);
        ~HypergeometricDistribution();

        double getRandomVaraible();
        void test(bool max_sampling);
    private:
        unsigned int N_; // количество экземл€ров
        unsigned int D_; // количество дефектных экзмепл€ров
        unsigned int n_; // размер выборочной группы

        long double* probs_{ nullptr }; // отрезок с веро€тност€ми
        unsigned int* vars_{ nullptr }; // этим веро€тност€м соответвуют случайные величины

        long double binomial_coefficient(unsigned int n, unsigned int k);
        double F(double x);
    };
}

