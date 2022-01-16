
long long maxRunTime(int n, vector<int> &batteries)
{
    long long l = 0, r = 0;
    for (int x : batteries)
        r += x;
    while (l < r)
    {
        long long m = (l + r + 1) >> 1;
        long long sum = 0;
        for (int x : batteries)
            sum += min((long long)x, m);
        if (sum >= m * n)
            l = m;
        else
            r = m - 1;
    }
    return l;
}