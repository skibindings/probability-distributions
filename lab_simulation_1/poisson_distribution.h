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
        double lambda_{ 0 }; // ������� ���������� ������� �� ������������� ���������� �������

        double significant_probability_{ 0.0 }; // ��������� ��������, ����������� ������� < significant_probability_, ���������� �� ��������� ��������� ��������, � ������� ����������� >= significant_probability_ � � ��� +1

        long double* probs_{ nullptr }; // ������� � �������������
        unsigned int probs_size_; // ���������� �������� ��������� �������
        unsigned int* vars_{ nullptr }; // ���� ������������ ����������� ��������� ��������

        double F(double x);
    };

}
