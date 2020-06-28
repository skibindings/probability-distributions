#pragma once
#include "probability_distribution.h"

namespace disrtibutions {

    class GeometricDistribution : public ProbabilityDistribution
    {
    public:
        GeometricDistribution(double p, double significant_probability);
        ~GeometricDistribution();

        double getRandomVaraible();
        void test(bool max_sampling);
    private:
        double p_{ 0 }; // вероятность победы
        double significant_probability_{ 0.0 }; // случайные величины, вероятности которых < significant_probability_, заменяются на последнюю случайную величину, у которой вероятность >= significant_probability_ и к ней +1

        double* probs_{ nullptr }; // отрезок с вероятностями
        unsigned int probs_size_; // количество значимых случайных величин
        double F(double x);
    };

}