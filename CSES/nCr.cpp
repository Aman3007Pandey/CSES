long long nCr(long long n, long long r)
{
    if (r > n)
        return 0;

    if (r == 0 || n == r)
        return 1;

    double res = 0;
    for (int i = 0; i < r; i++)
    {
        res += (log(n - i) - log(i + 1));
    }

    return round(exp(res));
}