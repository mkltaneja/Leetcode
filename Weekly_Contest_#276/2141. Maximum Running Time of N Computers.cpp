
// APPROACH 1 (Using Binary Search in sum of all batteries) --> O(m*log(sum))

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

// APPROACH 2 (Using Math) -> O(m*log(m))

long long maxRunTime(int n, vector<int> &batteries)
{
    sort(batteries.begin(), batteries.end());
    reverse(batteries.begin(), batteries.end());
    long long sum = 0;
    for (int x : batteries)
        sum += x;

    for (int x : batteries)
    {
        if (x <= sum / n)
            return sum / n;
        sum -= x;
        n--;
    }
    return 0;
}