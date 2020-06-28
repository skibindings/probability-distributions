#include "pch.h"
#include "bernoulli_distribution.h"

namespace disrtibutions {

    BernoulliDistribution::BernoulliDistribution(double p) : ProbabilityDistribution()
    {
        p_ = p;
    }

    BernoulliDistribution::~BernoulliDistribution()
    {
    }

    double BernoulliDistribution::getRandomVaraible() {
        lcg_seed = lcg->getNextRandomNumber(lcg_seed);
        double uniformed_number = lcg->uniform_number(lcg_seed);
        if (uniformed_number <= p_)
            return 1.0;
        return 0.0;
    }

    void BernoulliDistribution::test(bool max_sampling) {
        // ������� �������� ��������� �������
        double a = 0;
        double b = 1;

        unsigned int n = pow(2, 12); // (����� �������) 
        if (max_sampling) {
            n = lcg->getModulus();
        }
        unsigned int k = 2;

        double l = 1; // ����� ������ ���������

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

        //������� ������������� ������������ �
        p[0] = 1 - p_;
        p[1] = p_;
        //������� ��-�������
        double score = 0.0;
        for (unsigned int i = 0; i < k; i++) {
            // ������������ ��-�������
            score += pow(v[i] - n * p[i], 2) / n * p[i];
        }

        cout << "TEST BERNOULLI DISTRIBUTION" << endl;

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

    double BernoulliDistribution::F(double x) {
        return 0.0;
    }

}