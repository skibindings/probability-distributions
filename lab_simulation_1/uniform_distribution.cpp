#include "pch.h"
#include "uniform_distribution.h"

namespace disrtibutions {

    UniformDistribution::UniformDistribution(double a, double b) : ProbabilityDistribution()
    {
        a_ = a;
        b_ = b;
    }

    UniformDistribution::~UniformDistribution()
    {
    }

    double UniformDistribution::getRandomVaraible() {
        lcg_seed = lcg->getNextRandomNumber(lcg_seed);
        return a_ + lcg->uniform_number(lcg_seed, b_ - a_);
    }

    void UniformDistribution::test(bool max_sampling) {
        // отрезок значимых случайных величин
        double a = a_;
        double b = b_;

        unsigned int n = pow(2, 12); // (объём выборки) 
        if (max_sampling) {
            n = lcg->getModulus();
        }
        unsigned int k = 3.78 * pow((double)(n - 1), 2.0 / 5.0);

        double l = (b - a) / (double)k; // длина одного интервала

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
        double interval_start = a;
        double interval_end = 0;
        double score = 0.0;
        for (unsigned int i = 0; i < k; i++) {
            interval_end = interval_start + l;
            p[i] = F(interval_end) - F(interval_start); // нашли теоретическую вероятность
            interval_start = interval_end;

            // подсчитываем хи-квадрат
            score += pow(v[i] - n * p[i], 2) / n * p[i];
        }

        cout << "TEST UNIFORM DISTRIBUTION" << endl;

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

    double UniformDistribution::F(double x) {
        return (x - a_) / (b_ - a_);
    }

}