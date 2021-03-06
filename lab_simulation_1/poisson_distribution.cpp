#include "pch.h"
#include "poisson_distribution.h"


namespace disrtibutions {

    PoissonDistribution::PoissonDistribution(double lambda, double significant_probability) : ProbabilityDistribution()
    {
        lambda_ = lambda;
        significant_probability_ = significant_probability;

        // ����� ���������� ��������� ������� ��� ������� significant_probability
        vector<double> pre_probs = vector<double>();
        if (significant_probability > 0.0) {
            unsigned int i = 0;
            while (true) {
                double prob = pow(exp(1.0f),-lambda) * pow(lambda,i) / factorial(i);
                if (prob >= significant_probability) {
                    pre_probs.push_back(prob);
                    i++;
                }
                else if (i > lambda) break;
            }
        }

        //cout << "exp(1) = " << exp(1.0f) << endl;
        probs_size_ = pre_probs.size();

        probs_ = new long double[probs_size_];
        vars_ = new unsigned int[probs_size_];

        vector<pair<long double, unsigned int>> pre_probs_vars = vector<pair<long double, unsigned int>>(probs_size_);
        for (unsigned int i = 0; i < probs_size_; i++) {
            pre_probs_vars[i] = pair<long double, unsigned int>(pow(exp(1.0f), -lambda) * pow(lambda, i) / factorial(i), i);
        }

        auto comp = [&](const pair<long double, unsigned int> &a,
            const pair<long double, unsigned int> &b)-> bool {

            return a.first > b.first;
        };

        sort(pre_probs_vars.begin(), pre_probs_vars.end(), comp);

        for (unsigned int i = 0; i < probs_size_; i++) {
            probs_[i] = pre_probs_vars[i].first;
            vars_[i] = pre_probs_vars[i].second;
            if (i >= 1) {
                probs_[i] += probs_[i - 1];
            }
            //cout << vars_[i] << ":  " << probs_[i] << endl;
        }
        pre_probs_vars.clear();
    }

    PoissonDistribution::~PoissonDistribution()
    {
    }

    double PoissonDistribution::getRandomVaraible() {
        lcg_seed = lcg->getNextRandomNumber(lcg_seed);
        double uniformed_number = lcg->uniform_number(lcg_seed);
        for (unsigned int i = 0; i < probs_size_; i++) {
            if (uniformed_number <= probs_[i])
                return vars_[i];
        }
        return probs_size_; // ���� �� ����������� �� ������� � �� ����� ������ �����������, �� ������ �� � ������� �� ��������� �������, ���������� probs_size_ - ��������� �� ��������� ����. ������� � ������ 
    }

    void PoissonDistribution::test(bool max_sampling) {
        // ������� �������� ��������� �������
        double a = 0;
        double b = probs_size_;

        unsigned int n = pow(2, 12); // (����� �������) 
        if (max_sampling) {
            n = lcg->getModulus();
        }
        unsigned int k = b;

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

        //cout << missing;

        //������� ������������� ������������ � ��-�������, �����
        double score = 0.0;
        for (unsigned int i = 0; i < k; i++) {
            p[i] = pow(exp(1.0f), -lambda_) * pow(lambda_, i) / factorial(i); // ����� ������������� �����������

            // ������������ ��-�������
            score += pow(v[i] - n * p[i], 2) / n * p[i];
        }

        cout << "TEST POISSON DISTRIBUTION" << endl;

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

    double PoissonDistribution::F(double x) {
        return 0.0;
    }

}