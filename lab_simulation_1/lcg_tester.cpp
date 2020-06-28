#include "pch.h"
#include "lcg_tester.h"

LCGTester::LCGTester() {
    seeds_ = new unsigned int[kStreams];
}


LCGTester::~LCGTester() {
    delete[] seeds_;
}

// собирает данные для критериев и вычисляет хи квадраты (score)
// выход генератора нормируется на (0,d)
void LCGTester::test_lcg(FishmanLCG& lcg, unsigned int d) {
    d_ = d;

    frequency_score_ = 0;
    serial_score_ = 0;
    coupon_score_ = 0;
    poker_score_ = 0;

    long double* frequency_p = new long double[d_];
    unsigned int* frequency_v = new unsigned int[d_];
    for (unsigned int i = 0; i < d_; i++) {
        frequency_p[i] = 1.0 / (long double)d_;
        frequency_v[i] = 0;
    }

    long double* serial_p = new long double[d_*d_];
    unsigned int* serial_v = new unsigned int[d_*d_];
    for (unsigned int i = 0; i < d_*d_; i++) {
        serial_p[i] = 1.0 / (long double) (d_*d_);
        serial_v[i] = 0;
    }

    long double* coupon_p = new long double[max_coupon_size+1];
    unsigned int* coupon_v = new unsigned int[max_coupon_size+1];
    long double remaining_p = 0.0;
    for (unsigned int i = 0; i < max_coupon_size; i++) {
        coupon_p[i] = (long double)(d-1) / (long double)pow(d,i+1);
        coupon_v[i] = 0;

        remaining_p += coupon_p[i];
    }
    remaining_p = 1.0 - remaining_p;
    coupon_p[max_coupon_size] = remaining_p;

    long double* poker_p = new long double[5];
    unsigned int* poker_v = new unsigned int[5]; // хранит количество комбинаций с 1, 2, 3, 4, 5 различными числами
    for (unsigned int i = 0; i < max_coupon_size; i++) {
        poker_p[i] = calculate_poker_probability(i + 1);
        poker_v[i] = 0;
    }

    collect_seeds(lcg);

    for (unsigned int step = 0; step < kStreams; step++) {
        collect_combinations(lcg, seeds_[step], frequency_v, serial_v, coupon_v, poker_v);
    }

    frequency_score_ = calculate_score(d_, kSequenceSize, frequency_v, frequency_p);
    cout << "frequency score = " << frequency_score_ << endl;

    serial_score_ = calculate_score(d_*d_, kSequenceSize / 2, serial_v, serial_p);
    cout << "serial score = " << serial_score_ << endl;

    coupon_score_ = calculate_score(max_coupon_size + 1, kSequenceSize * (((long double)d_ - 1.0) / (long double)d_), coupon_v, coupon_p);
    cout << "coupon score = " << coupon_score_ << endl;

    poker_score_ = calculate_score(5, kSequenceSize / 5, poker_v, poker_p);
    cout << "poker score = " << poker_score_ << endl;
}

bool LCGTester::check_frequecny_criteria(double reliability) {
    double quantile = goldstein_approximation(d_ - 1, reliability);
    return frequency_score_ < quantile;
}


bool LCGTester::check_serial_criteria(double reliability) {
    double quantile = goldstein_approximation(d_ * d_ - 1, reliability);
    return serial_score_ < quantile;
}


bool LCGTester::check_coupon_criteria(double reliability) {
    double quantile = goldstein_approximation(max_coupon_size, reliability);
    return coupon_score_ < quantile;
}


bool LCGTester::check_poker_criteria(double reliability) {
    double quantile = goldstein_approximation(4, reliability);
    return poker_score_ < quantile;
}

// расчёт хи квадрат
double LCGTester::calculate_score(unsigned int N, unsigned int n, unsigned int* v, long double* p) {
    long double score = 0.0;
    for (int i = 0; i < N; i++) {
        cout << v[i] << endl;
        score += powl(v[i] - n*p[i], 2) / (long double) (n*p[i]);
    }
    return score;
}

// аппроксимация Голдштейна, чтобы вычислить табличное значение квантили хи-квадрат
double LCGTester::goldstein_approximation(unsigned int n, double alpha) {
    double a[7] = { 1.0000886, 0.4713941, 0.0001348028, -0.008553069, 0.00312558, -0.0008426812, 0.00009780499 };
    double b[7] = { -0.2237368, 0.02607083, 0.01128186, -0.01153761, 0.005169654, 0.00253001, -0.001450117 };
    double c[7] = { -0.01513904, -0.008986007, 0.02277679, -0.01323293, -0.006950356, 0.001060438, 0.001565326 };

    double d;

    if (alpha >= 0.001 && alpha < 0.5) {
        d = -2.0637*pow(log(1.0 / alpha) - 0.16, 0.4274) + 1.5774;
    }
    else if (alpha <= 0.999) {
        d = 2.0637*pow(log(1.0 / (1.0-alpha)) - 0.16, 0.4274) - 1.5774;
    }

    double approximation = 0.0;

    for (int i = 0; i <= 6; i++) {
        approximation += pow(n, (-(double)i) / 2.0) * pow(d, i) * (a[i] + b[i] / n + (c[i] / pow((double) n, 2.0)));
    }

    approximation = pow(approximation, 3.0) * (double) n;

    return approximation;
}

// считаем теоретиеские вероятности для критерия покера
double LCGTester::calculate_poker_probability(unsigned int r) {
    unsigned int stirling_numbers[5] {1, 15, 25, 10, 1};
    long double probability = 1.0;
    for (unsigned int i = d_; i >= d_ - r + 1; i--) {
        probability *= i;
    }
    probability *= stirling_numbers[r - 1];
    probability /= pow(d_, 5);

    return probability;
}

// ищем kStreams сидов, обеспечивая разбиения последовательности на kStreams частей
void LCGTester::collect_seeds(FishmanLCG& lcg) {
    unsigned int count = kSequecePartSize;
    unsigned int seed_number = 0;
    unsigned int random_number = lcg.getInitialSeed();

    for (unsigned int i = 0; i < kSequenceSize; i++) {
        if (count == kSequecePartSize) {
            seeds_[seed_number] = random_number;
            seed_number++;
            count = 0;
            cout << seed_number << " seed is " << random_number << endl;
        }
        random_number = lcg.getNextRandomNumber(random_number);
        count++;
    }
}

// метод обеспечивающий подсчет количеств комбинаций для различных критериев
void LCGTester::collect_combinations(FishmanLCG& lcg, unsigned int& seed, unsigned int* f_v, unsigned int* s_v, unsigned int* c_v, unsigned int* p_v) {

    // данные для подсчета купонов
    unsigned int previous_number = -1;
    unsigned int coupon_size = 1;

    set<unsigned int> numbers_set = set<unsigned int>();

    for (unsigned int i = 0; i < kSequecePartSize; i += 10) {
        for (unsigned int j = 0; j < 10; j++) {
            unsigned int uniformed_number = lcg.uniform_number(seed, d_);
            seed = lcg.getNextRandomNumber(seed);

            // критерий равномерности
            f_v[uniformed_number] ++;

            // критерий серий
            if ((j + 1) % 2 == 0) {
                s_v[previous_number * d_ + uniformed_number] ++;
            }
            
            // критерий покера
            numbers_set.insert(uniformed_number);
            if ((j + 1) % 5 == 0) {
                p_v[numbers_set.size()-1]++;
                numbers_set.clear();
            }
            
            // критерий купонов
            if (uniformed_number == previous_number) {
                coupon_size++;
            }
            else {
                if (coupon_size <= max_coupon_size) {
                    c_v[coupon_size - 1]++;
                }
                else {
                    c_v[max_coupon_size]++;
                }
                coupon_size = 1;
            }

            previous_number = uniformed_number;
        }
    }
}