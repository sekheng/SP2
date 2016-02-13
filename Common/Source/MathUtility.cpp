#include "MathUtility.h"

int factorial(int n)
{
    if (n <= 1) {
        return 1;
    }
    return factorial(n - 1) * n;
}

int nCr(int n, int r)
{
    int value = nPr(n, r);
    if (value <= 1)
        return 1;
    r = factorial(r);
    return (value / r);
}

int nPr(int n, int r)
{
    int value = n - r;
    if (value == 0)
    {
        value = 1;
    }
    else if (value < 0)
    {
        return 1;
    }
    return (factorial(n) / factorial(value));
}

int nTermAP(int a, int d, int n)
{
    if (n >= 1)
        return a + (d * (n - 1));
    else {
        return 0;
    }
}

int summationAP(int a, int d, int n)
{
    if (n == 1)
    {
        return a;
    }
    else if (n < 1)
    {
        return 0;
    }
    return summationAP(a, d, n - 1) + nTermAP(a, d, n);
}

int nTermGP(int a, int r, int n)
{
    return a * static_cast<int>(pow(r, n - 1));
}

int summationGP(int a, int r, int n)
{
    if (n <= 1)
        return a;
	return summationGP(a, r, n - 1) + nTermGP(a, r, n);
}