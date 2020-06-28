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

    // �������� ������ ��� ��������� � ��������� �� �������� (score)
    void test_lcg(FishmanLCG& lcg, unsigned int d);

    // �������� ��������� � ��������� ������������� reliability
    // true - �������� �����������, false - �������� �� �����������
    bool check_frequecny_criteria(double reliability);
    bool check_serial_criteria(double reliability);
    bool check_coupon_criteria(double reliability);
    bool check_poker_criteria(double reliability);

private:

    // ����� �������������� ������� ��������� ���������� ��� ��������� ���������
    void collect_combinations(FishmanLCG& lcg, unsigned int& seed, unsigned int* f_v, unsigned int* s_v, unsigned int* c_v, unsigned int* p_v);
    // ���� kStreams �����, ����������� ��������� ������������������ �� kStreams ������
    void collect_seeds(FishmanLCG& lcg);

    // ������ �� �������
    double calculate_score(unsigned int N, unsigned int n, unsigned int* v, long double* p);
    // ������� ������������ ����������� ��� �������� ������
    double calculate_poker_probability(unsigned int r);

    unsigned int d_{ 0 };
    unsigned int max_coupon_size{ 5 }; // ������������ ������ ������ ��� ����� ��������
    unsigned int* seeds_{ nullptr };
    
    // �������� ��-������� ��� ��������� ���������
    double frequency_score_{ 0 };
    double serial_score_{ 0 };
    double poker_score_{ 0 };
    double coupon_score_{ 0 };

    // ������������� ����������, ����� ��������� ��������� �������� �������� ��-�������
    double goldstein_approximation(unsigned int n, double alpha);

    const unsigned int kSequenceSize{ (unsigned int) pow(2,31) }; // ������ ������������������, ������� ����� �����������
    const unsigned int kStreams{ 8 }; // ���������� �������
    const unsigned int kSequecePartSize { kSequenceSize / kStreams };
};

