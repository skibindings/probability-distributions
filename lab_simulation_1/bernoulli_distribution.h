#pragma once
#include "probability_distribution.h"

namespace disrtibutions {

    class BernoulliDistribution : public ProbabilityDistribution
    {
    public:
        BernoulliDistribution(double p);
        ~BernoulliDistribution();

        double getRandomVaraible();
        void test(bool max_sampling);
    private:
        double p_{ 0 }; // вероятность победы

        double F(double x);
    };

}