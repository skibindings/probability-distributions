#pragma once
#define _USE_MATH_DEFINES

#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "fishman_lcg.h"
#include "factorial.h"

using namespace std;

namespace disrtibutions {

    // родительский класс всех распределений
    class ProbabilityDistribution
    {
    public:
        ProbabilityDistribution();
        ~ProbabilityDistribution();

        virtual double getRandomVaraible() = 0; // получить очередную случайную величину распределения
        virtual void test(bool max_sampling) = 0; // проверка гипотезы на распределение флаг max_sampling задействует максимально возможную выборку (в соотвествии с ЛКГ) для проверки гипотезы

        // аппроксимация Голдштейна, чтобы вычислить табличное значение квантили хи-квадрат
        static double goldstein_approximation(unsigned int n, double alpha) {
            double a[7] = { 1.0000886, 0.4713941, 0.0001348028, -0.008553069, 0.00312558, -0.0008426812, 0.00009780499 };
            double b[7] = { -0.2237368, 0.02607083, 0.01128186, -0.01153761, 0.005169654, 0.00253001, -0.001450117 };
            double c[7] = { -0.01513904, -0.008986007, 0.02277679, -0.01323293, -0.006950356, 0.001060438, 0.001565326 };

            double d;

            if (alpha >= 0.001 && alpha < 0.5) {
                d = -2.0637*pow(log(1.0 / alpha) - 0.16, 0.4274) + 1.5774;
            }
            else if (alpha <= 0.999) {
                d = 2.0637*pow(log(1.0 / (1.0 - alpha)) - 0.16, 0.4274) - 1.5774;
            }

            double approximation = 0.0;

            for (int i = 0; i <= 6; i++) {
                approximation += pow(n, (-(double)i) / 2.0) * pow(d, i) * (a[i] + b[i] / n + (c[i] / pow((double)n, 2.0)));
            }

            approximation = pow(approximation, 3.0) * (double)n;

            return approximation;
        }

    protected:

        FishmanLCG* lcg{ nullptr }; // лкг необходимый для моделирования распределений
        unsigned int lcg_seed{ 1 }; // храним для каждого экзпемляра распределения сид в лкг 

        virtual double F(double x) = 0; // функция распределения или её приблизительное значение, нужно для проверки гипотезы о распределении
    };

}