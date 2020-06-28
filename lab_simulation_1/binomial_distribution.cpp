#include "pch.h"
#include "binomial_distribution.h"

namespace disrtibutions {


    BinomialDistribution::BinomialDistribution(unsigned int n, double p) : ProbabilityDistribution()
    {
        n_ = n;
        p_ = p;

        probs_ = new double[n+1];
        vars_ = new unsigned int[n + 1];

        vector<pair<double, unsigned int>> pre_probs_vars = vector<pair<double, unsigned int>>(n + 1);
        for (unsigned int i = 0; i <= n; i++) {
            pre_probs_vars[i] = pair<double, unsigned int>(binomial_coefficient(n, i) * pow(p, i) * pow(1 - p, n - i),i);
        }

        auto comp = [&](const pair<double, unsigned int> &a,
            const pair<double, unsigned int> &b)-> bool {

            return a.first > b.first;
        };

        sort(pre_probs_vars.begin(), pre_probs_vars.end(), comp);

        for (unsigned int i = 0; i <= n; i++) {
            probs_[i] = pre_probs_vars[i].first;
            vars_[i] = pre_probs_vars[i].second;
            if (i >= 1) {
                probs_[i] += probs_[i - 1];
            }
            //cout << vars_[i] << ":  " << probs_[i] << endl;
        }
        pre_probs_vars.clear();
    }


    BinomialDistribution::~BinomialDistribution()
    {
        delete[] probs_;
        delete[] vars_;
    }


    double BinomialDistribution::getRandomVaraible() {
        lcg_seed = lcg->getNextRandomNumber(lcg_seed);
        double uniformed_number = lcg->uniform_number(lcg_seed);
        for (unsigned int i = 0; i <= n_; i++) {
            if (uniformed_number <= probs_[i])
                return vars_[i];
        }
        return vars_[n_];
    }


    long double BinomialDistribution::binomial_coefficient(unsigned int n, unsigned int k) {
        if (k == 0 || k == n)
            return 1;

        return factorial(n) / factorial(k) / factorial(n - k);
    }

    void BinomialDistribution::test(bool max_sampling) {
        // отрезок значимых случайных величин
        double a = 0;
        double b = n_+1;

        unsigned int n = pow(2, 12); // (объём выборки) 
        if (max_sampling) {
            n = lcg->getModulus();
        }
        unsigned int k = b;

        double l = 1; // длина одного интервала

        unsigned int* v = new unsigned int[k]; // количество попаданий в 1-ый ... k-ый интрвалы 
        double* p = new double[k]; // теоретические вероятности попадания в 1-ый ... k-ый интервалы

        for (unsigned int i = 0; i < k; i++) {
            v[i] = 0;
            p[i] = 0.0;
        }

        int missing = 0;
        //сбор эмпирических данных
        for (unsigned int i = 0; i < n; i++) {
            unsigned int interval_number = getRandomVaraible() / l;
            if (interval_number >= 0 && interval_number < k)
                v[interval_number]++;
            else
                missing++;
        }

        //подсчет теоретических вероятностей и хи-квадрат, сразу
        double score = 0.0;
        for (unsigned int i = 0; i < k; i++) {
            p[i] = binomial_coefficient(n_, i) * pow(p_, i) * pow(1 - p_, n_ - i); // нашли теоретическую вероятность

            // подсчитываем хи-квадрат
            score += pow(v[i] - n * p[i], 2) / n * p[i];
        }

        cout << "TEST BINOMIAL DISTRIBUTION" << endl;

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

    double BinomialDistribution::F(double x) {
        return 0.0;
    }

}