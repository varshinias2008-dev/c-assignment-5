#include <stdio.h>

long long calls = 0;

int sum_digits(int n)
{
    if (n < 10)
        return n;

    return (n % 10) + sum_digits(n / 10);
}

int digital_root(int n)
{
    if (n < 10)
        return n;

    return digital_root(sum_digits(n));
}

long long power_linear(long long base, int exp)
{
    calls++;

    if (exp == 0)
        return 1;

    return base * power_linear(base, exp - 1);
}

long long power_fast(long long base, int exp)
{
    long long half;

    calls++;

    if (exp == 0)
        return 1;

    half = power_fast(base, exp / 2);

    if (exp % 2 == 0)
        return half * half;

    return base * half * half;
}

long long power_iterative(long long base, int exp)
{
    long long result = 1;

    while (exp > 0)
    {
        if (exp % 2 == 1)
            result *= base;

        base *= base;
        exp /= 2;
    }

    return result;
}

int main(void)
{
    int tests[] = {0, 1, 25, 9875, 99999};
    int values[] = {10, 100, 1000, 10000};
    int i;
    long long result;

    printf("DIGITAL ROOT TESTING\n");
    for (i = 0; i < 5; i++)
        printf("%d -> %d\n", tests[i], digital_root(tests[i]));

    printf("\nPOWER FUNCTION TESTING\n");

    calls = 0;
    result = power_linear(2, 30);
    printf("Linear: %lld\n", result);
    printf("Linear calls: %lld\n", calls);

    calls = 0;
    result = power_fast(2, 30);
    printf("Fast: %lld\n", result);
    printf("Fast calls: %lld\n", calls);

    printf("Iterative: %lld\n", power_iterative(2, 30));

    printf("\nCALL COUNT MEASUREMENT (base = 1)\n");
    printf("n\tLinear calls\tFast calls\n");

    for (i = 0; i < 4; i++)
    {
        int n = values[i];
        long long linear_calls, fast_calls;

        calls = 0;
        power_linear(1, n);
        linear_calls = calls;

        calls = 0;
        power_fast(1, n);
        fast_calls = calls;

        printf("%d\t%lld\t\t%lld\n", n, linear_calls, fast_calls);
    }

    return 0;
}

Sample output:

DIGITAL ROOT TESTING
0 -> 0
1 -> 1
25 -> 7
9875 -> 2
99999 -> 9

POWER FUNCTION TESTING
Linear: 1073741824
Linear calls: 31
Fast: 1073741824
Fast calls: 6
Iterative: 1073741824

CALL COUNT MEASUREMENT (base = 1)
n       Linear calls    Fast calls
10      11              5
100     101             8
1000    1001            11
10000   10001           15

Compile and run:
gcc -std=c11 -Wall -Wextra b1.c -o b1
./b1
