#include "pch.h"
#include "probability_distribution.h"

namespace disrtibutions {

    ProbabilityDistribution::ProbabilityDistribution()
    {
        lcg = new FishmanLCG();
    }


    ProbabilityDistribution::~ProbabilityDistribution()
    {
        delete lcg;
    }

}