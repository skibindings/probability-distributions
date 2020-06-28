#pragma once
#include "probability_distribution.h"

namespace disrtibutions {

    class PoissonDistribution : public ProbabilityDistribution
    {
    public:
        PoissonDistribution(double lambda, double significant_probability);
        ~PoissonDistribution();

        double getRandomVaraible();
        void test(bool max_sampling);
    private:
        double lambda_{ 0 }; // среднее количество событий за фиксированный промежуток времени

        double significant_probability_{ 0.0 }; // случайные величины, вероятности которых < significant_probability_, заменяются на последнюю случайную величину, у которой вероятность >= significant_probability_ и к ней +1

        long double* probs_{ nullptr }; // отрезок с вероятностями
        unsigned int probs_size_; // количество значимых случайных величин
        unsigned int* vars_{ nullptr }; // этим вероятностям соответвуют случайные величины

        double F(double x);
    };

}
