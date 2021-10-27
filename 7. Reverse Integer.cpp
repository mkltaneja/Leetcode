
int reverse(int x)
{
    long ans = 0;
    bool neg = (x < 0);
    x = abs(x);
    while (x)
    {
        ans *= 10;
        ans += x % 10;
        x /= 10;
    }

    return (ans > INT_MAX || ans < INT_MIN) ? 0 : (neg ? -ans : ans);
}