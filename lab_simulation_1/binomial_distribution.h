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
        double p_; // ����������� ������ ��������
        unsigned int n_; // ���������� ���������

        double* probs_{ nullptr }; // ������� � �������������
        unsigned int* vars_{ nullptr }; // ���� ������������ ����������� ��������� ��������

        long double binomial_coefficient(unsigned int n, unsigned int k);
        double F(double x);
    };

}
