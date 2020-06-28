#include "pch.h"
#include "normal_distribution.h"


namespace disrtibutions {

    NormalDistribution::NormalDistribution(double mean, double variance) : ProbabilityDistribution()
    {
        mean_ = mean;
        variance_ = variance;
        scale_ = sqrt(variance);
    }

    NormalDistribution::~NormalDistribution()
    {
    }

    double NormalDistribution::getRandomVaraible() {
        lcg_seed = lcg->getNextRandomNumber(lcg_seed);
        double first_uniform = lcg->uniform_number(lcg_seed);
        lcg_seed = lcg->getNextRandomNumber(lcg_seed);
        double second_uniform = lcg->uniform_number(lcg_seed);

        return sqrt(-2.0*log(first_uniform))*sin(2.0*M_PI*second_uniform) * scale_ + mean_;
    }

    void NormalDistribution::test(bool max_sampling) {
        // отрезок значимых случайных величин
        double a = mean_ - 1 - scale_ * 5;
        double b = mean_ + 1 + scale_ * 5;

        unsigned int n = pow(2, 12); // (объём выборки) 
        if (max_sampling) {
            n = lcg->getModulus() / 2;
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

        cout << "TEST NORMAL DISTRIBUTION" << endl;

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

    double NormalDistribution::F(double x) {
        x = (x - mean_) / scale_;
        if(x > 0)
            return 1.0 - 0.852 * exp(-pow((x + 1.5774) / 2.0637, 2.34));
        return 0.852 * exp(-pow((-x + 1.5774) / 2.0637, 2.34));
    }

}