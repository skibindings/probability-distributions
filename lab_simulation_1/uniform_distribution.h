#pragma once
#include "probability_distribution.h"

namespace disrtibutions {

    class UniformDistribution : public ProbabilityDistribution
    {
    public:
        UniformDistribution(double a, double b);
        ~UniformDistribution();

        double getRandomVaraible();
        void test(bool max_sampling);
    private:
        double a_{ 0 };
        double b_{ 0 };

        double F(double x);
    };

}
