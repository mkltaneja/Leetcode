
int mod = 1e9 + 7;

long long int pow(long long int a, long long int b)
{
    long long int ans = 1;
    while (b)
    {
        if (b & 1)
            ans = (ans * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return ans % mod;
}

int maxNiceDivisors(int n)
{
    if (n == 1)
        return 1;
    if (n % 3 == 0)
        return (pow(3, n / 3) % mod);
    if (n % 3 == 1)
        return (4 * pow(3, n / 3 - 1) % mod);
    return (2 * pow(3, n / 3) % mod);
}