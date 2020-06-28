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
        double p_{ 0 }; // ����������� ������
        double significant_probability_{ 0.0 }; // ��������� ��������, ����������� ������� < significant_probability_, ���������� �� ��������� ��������� ��������, � ������� ����������� >= significant_probability_ � � ��� +1

        double* probs_{ nullptr }; // ������� � �������������
        unsigned int probs_size_; // ���������� �������� ��������� �������
        double F(double x);
    };

}