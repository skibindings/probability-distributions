#pragma once
#include "probability_distribution.h"

namespace disrtibutions {

    class NormalDistribution : public ProbabilityDistribution
    {
    public:
        NormalDistribution(double mean, double variance);
        ~NormalDistribution();

        double getRandomVaraible();
        void test(bool max_sampling);
    private:
        double variance_;
        double mean_;
        double scale_;

        double F(double x);
    };

}