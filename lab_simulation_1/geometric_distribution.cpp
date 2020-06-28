#include "pch.h"
#include "geometric_distribution.h"

namespace disrtibutions {

    GeometricDistribution::GeometricDistribution(double p, double significant_probability) : ProbabilityDistribution()
    {
        p_ = p;
        significant_probability_ = significant_probability;

        // ����� ���������� ��������� ������� ��� ������� significant_probability
        vector<double> pre_probs = vector<double>();
        if (significant_probability > 0.0) {
            unsigned int i = 1;
            while (true) {
                double prob = p * pow(1 - p, i - 1);
                if (prob >= significant_probability) {
                    pre_probs.push_back(prob);
                    i++;
                }
                else break;
            }
        }
        
        //��������� �������
        probs_size_ = pre_probs.size();
        probs_ = new double[probs_size_];
        for (unsigned int i = 0; i < probs_size_; i++) {
            probs_[i] = pre_probs[i];
            if (i >= 1) {
                probs_[i] += probs_[i - 1];
            }
            //cout << probs_[i] << endl;
        }

        pre_probs.clear();
    }


    GeometricDistribution::~GeometricDistribution()
    {
        delete[] probs_;
    }


    double GeometricDistribution::getRandomVaraible() {
        lcg_seed = lcg->getNextRandomNumber(lcg_seed);
        double uniformed_number = lcg->uniform_number(lcg_seed);
        for (unsigned int i = 0; i < probs_size_; i++) {
            if (uniformed_number <= probs_[i])
                return i;
        }
        return probs_size_; // ���� �� ����������� �� ������� � �� ����� ������ �����������, �� ������ �� � ������� �� ��������� �������, ���������� probs_size_ - ��������� �� ��������� ����. ������� � ������ 
    }

    void GeometricDistribution::test(bool max_sampling) {
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


        //������� ������������� ������������ � ��-�������, �����
        double score = 0.0;
        for (unsigned int i = 0; i < k; i++) {
            p[i] = p_ * pow(1 - p_, i); // ����� ������������� �����������

            // ������������ ��-�������
            score += pow(v[i] - n * p[i], 2) / n * p[i];
        }

        cout << "TEST GEOMETRIC DISTRIBUTION" << endl;

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

    double GeometricDistribution::F(double x) {
        return 0.0;
    }

}