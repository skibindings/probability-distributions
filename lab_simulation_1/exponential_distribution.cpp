#include "pch.h"
#include "exponential_distribution.h"

namespace disrtibutions {

    ExponentialDistribution::ExponentialDistribution(double lambda) : ProbabilityDistribution()
    {
        lambda_ = lambda;
    }

    ExponentialDistribution::~ExponentialDistribution()
    {
    }

    double ExponentialDistribution::getRandomVaraible() {
        lcg_seed = lcg->getNextRandomNumber(lcg_seed);
        double uniformed_var = lcg->uniform_number(lcg_seed);

        return -log(uniformed_var) / lambda_;
    }

    void ExponentialDistribution::test(bool max_sampling) {
        // ������� �������� ��������� �������
        double a = 0.0;
        double b = 4.0 + 4.0*(1 / lambda_); // ��� ������ ������, ��� ������� ����������� ����������� ��������� ������� ��������� �� 0.0

        unsigned int n = pow(2, 12); // (����� �������) 
        if (max_sampling) {
            n = lcg->getModulus();
        }
        unsigned int k = 3.78 * pow((double)(n - 1), 2.0 / 5.0); // ��� ������� n, ������� ������ k (k - ���������� ��������� (����������))

        double l = (b - a) / (double)k; // ����� ������ ���������

        unsigned int* v = new unsigned int[k]; // ���������� ��������� � 1-�� ... k-�� �������� 
        double* p = new double[k]; // ������������� ����������� ��������� � 1-�� ... k-�� ���������

        for (unsigned int i = 0; i < k; i++) {
            v[i] = 0;
            p[i] = 0.0;
        }

        int missing = 0;
        //���� ������������ ������
        for (unsigned int i = 0; i < n; i++) {
            unsigned int interval_number = getRandomVaraible() / l;
            if (interval_number >= 0 && interval_number < k)
                v[interval_number]++;
            else
                missing++;
        }

        //������� ������������� ������������ � ��-�������, �����
        double interval_start = a;
        double interval_end = 0;
        double score = 0.0;
        for (unsigned int i = 0; i < k; i++) {
            interval_end = interval_start + l;
            p[i] = F(interval_end) - F(interval_start); // ����� ������������� �����������
            interval_start = interval_end;

            // ������������ ��-�������
            score += pow(v[i] - n * p[i], 2) / n * p[i];
        }

        cout << "TEST EXPONENTIAL DISTRIBUTION" << endl;

        cout << "score = " << score << endl;
        double hypoth = ProbabilityDistribution::goldstein_approximation(k - 1, 0.95f);
        cout << "hypoth = " << hypoth << endl;

        if (score < hypoth) {
            cout << "Hypothesis is accepted with 95% trust" << endl << "Distribution model is correct!" << endl;
        }
        else {
            cout << "Hypothesis is declined" << endl << "Distribution model is incorrect!" << endl;
        }

        cout << endl << endl << endl;
        
        delete[] v;
        delete[] p;
    }

    double ExponentialDistribution::F(double x) {
        return 1 - exp(-lambda_ * x);
    }

}