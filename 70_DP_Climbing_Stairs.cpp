// RECURSION
// TLE
int rec_ways(int i, int n)
{
    if (i == n)
        return 1;
    int count = 0;
    for (int jump = 1; jump <= 2 && i + jump <= n; jump++)
    {
        count += rec_ways(i + jump, n);
    }
    return count;
}

int climbStairs(int n)
{
    return rec_ways(0, n);
}

// MEMOISATION
// accepted
int dp_ways(int i, int n, vector<int> &dp)
{
    if (i == n)
        return dp[i] = 1;
    if (dp[i] != 0)
        return dp[i];
    int count = 0;
    for (int jump = 1; jump <= 2 && i + jump <= n; jump++)
    {
        count += dp_ways(i + jump, n, dp);
    }
    return dp[i] = count;
}

int climbStairs(int n)
{
    if (n == 0)
        return 1;
    vector<int> dp(n + 1, 0);
    return dp_ways(0, n, dp);
}
// TABULATION
// accepted
int tab_ways(int i, int n, vector<int> &dp)
{
    for (int i = n; i >= 0; i--)
    {
        if (i == n)
        {
            dp[i] = 1;
            continue;
        }
        for (int jump = 1; jump <= 2 && i + jump <= n; jump++)
        {
            dp[i] += dp[i + jump];
        }
    }
    return dp[0];
}

int climbStairs(int n)
{
    if (n == 0)
        return 1;
    vector<int> dp(n + 1, 0);
    return tab_ways(0, n, dp);
}

// optimization
// accepted
int opt_ways(int i, int n)
{
    int a = 1;
    int b = 1;
    int sum = 1;
    for (int i = 2; i <= n; i++)
    {
        sum = a + b;
        a = b;
        b = sum;
    }
    return sum;
}

int climbStairs(int n)
{
    if (n == 0)
        return 1;
    return tab_ways(0, n);
}