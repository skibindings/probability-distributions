#pragma once
#include "probability_distribution.h"

namespace disrtibutions {

    class HypergeometricDistribution : public ProbabilityDistribution
    {
    public:
        HypergeometricDistribution(unsigned int N, unsigned int D, unsigned int n);
        ~HypergeometricDistribution();

        double getRandomVaraible();
        void test(bool max_sampling);
    private:
        unsigned int N_; // ���������� ����������
        unsigned int D_; // ���������� ��������� �����������
        unsigned int n_; // ������ ���������� ������

        long double* probs_{ nullptr }; // ������� � �������������
        unsigned int* vars_{ nullptr }; // ���� ������������ ����������� ��������� ��������

        long double binomial_coefficient(unsigned int n, unsigned int k);
        double F(double x);
    };
}

