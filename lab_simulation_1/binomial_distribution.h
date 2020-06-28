#pragma once
#include "probability_distribution.h"
#include <utility> 

namespace disrtibutions {

    class BinomialDistribution : public ProbabilityDistribution
    {
    public:
        BinomialDistribution(unsigned int n, double p);
        ~BinomialDistribution();

        double getRandomVaraible();
        void test(bool max_sampling);
    private:
        double p_; // вероятность одного выйгрыша
        unsigned int n_; // количество испытаний

        double* probs_{ nullptr }; // отрезок с вероятностями
        unsigned int* vars_{ nullptr }; // этим вероятностям соответвуют случайные величины

        long double binomial_coefficient(unsigned int n, unsigned int k);
        double F(double x);
    };

}
