#include "pch.h"
#include <iostream>
#include <math.h>
#include <omp.h>
#include <vector>

#include "bernoulli_distribution.h"
#include "binomial_distribution.h"
#include "geometric_distribution.h"
#include "hypergeometric_distribution.h"
#include "hypergeometric_distribution.h"
#include "poisson_distribution.h"
#include "exponential_distribution.h"
#include "normal_distribution.h"
#include "uniform_distribution.h"

using namespace std;
using namespace disrtibutions;

int main()
{
    vector<ProbabilityDistribution*> probabilityDistributions = vector<ProbabilityDistribution*>();
    probabilityDistributions.push_back(new ExponentialDistribution(0.8));
    probabilityDistributions.push_back(new NormalDistribution(-2, 4));
    probabilityDistributions.push_back(new UniformDistribution(-5, 15));
    probabilityDistributions.push_back(new BinomialDistribution(20, 0.5));
    probabilityDistributions.push_back(new GeometricDistribution(0.4, 0.0001));
    probabilityDistributions.push_back(new HypergeometricDistribution(40, 20, 20));
    probabilityDistributions.push_back(new PoissonDistribution(5, 0.0001));
    probabilityDistributions.push_back(new BernoulliDistribution(0.4));

    // тестируем распределения
    for (int i = 0; i < probabilityDistributions.size(); i++) {
        probabilityDistributions[i]->test(false); // если нужна максимальная выборка, ставьте флажок true
    }
}
