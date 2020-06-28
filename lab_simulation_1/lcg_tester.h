#pragma once
#include <iostream>
#include <math.h>
#include <set>

#include "fishman_lcg.h"

using namespace std;

class LCGTester
{
public:
    LCGTester();
    ~LCGTester();

    // собирает данные для критериев и вычисляет хи квадраты (score)
    void test_lcg(FishmanLCG& lcg, unsigned int d);

    // проверка критериев с процентом достоверности reliability
    // true - гипотеза выполняется, false - гипотеза не выполняется
    bool check_frequecny_criteria(double reliability);
    bool check_serial_criteria(double reliability);
    bool check_coupon_criteria(double reliability);
    bool check_poker_criteria(double reliability);

private:

    // метод обеспечивающий подсчет количеств комбинаций для различных критериев
    void collect_combinations(FishmanLCG& lcg, unsigned int& seed, unsigned int* f_v, unsigned int* s_v, unsigned int* c_v, unsigned int* p_v);
    // ищем kStreams сидов, обеспечивая разбиения последовательности на kStreams частей
    void collect_seeds(FishmanLCG& lcg);

    // расчёт хи квадрат
    double calculate_score(unsigned int N, unsigned int n, unsigned int* v, long double* p);
    // считаем теоретиеские вероятности для критерия покера
    double calculate_poker_probability(unsigned int r);

    unsigned int d_{ 0 };
    unsigned int max_coupon_size{ 5 }; // максимальный размер купона для купон критерия
    unsigned int* seeds_{ nullptr };
    
    // значения хи-квадрат для различных критериев
    double frequency_score_{ 0 };
    double serial_score_{ 0 };
    double poker_score_{ 0 };
    double coupon_score_{ 0 };

    // аппроксимация Голдштейна, чтобы вычислить табличное значение квантили хи-квадрат
    double goldstein_approximation(unsigned int n, double alpha);

    const unsigned int kSequenceSize{ (unsigned int) pow(2,31) }; // размер последовательности, которую будем исследовать
    const unsigned int kStreams{ 8 }; // количество потоков
    const unsigned int kSequecePartSize { kSequenceSize / kStreams };
};

