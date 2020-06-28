#pragma once
#include "probability_distribution.h"

namespace disrtibutions {

    class ExponentialDistribution : public ProbabilityDistribution
    {
    public:
        ExponentialDistribution(double lambda);
        ~ExponentialDistribution();

        double getRandomVaraible();
        void test(bool max_sampling);
    private:
        double lambda_{ 0 }; // параметр

        double F(double x);
    };

}
