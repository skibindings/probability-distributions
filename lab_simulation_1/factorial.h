#pragma once
inline long double factorial(long double n)
{
    if (n > 1)
        return n * factorial(n - 1);
    else
        return 1;
}