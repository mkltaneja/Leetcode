
// METHOD 1 (Bottom Up)

int mod = 1000000007;
int rearrangeSticks(int n, int k)
{
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    dp[1][1] = 1;
    for (int i = 2; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            int smaller = dp[i - 1][j];
            int largest = dp[i - 1][j - 1];
            dp[i][j] = (((long long)(i - 1) * smaller) % mod + largest) % mod;
        }
    }
    return dp[n][k];
}

// METHOD 2 (Recursive -- More space and Time OPTIMIZED)

int mod = 1000000007;
long dp[1005][1005];
int rearrangeSticks(int n, int k)
{
    if (n == k)
        return dp[n][k] = 1;
    if (n == 0 || k == 0)
        return dp[n][k] = 0;
    if (dp[n][k])
        return dp[n][k];
    long ans = 0;
    ans += (long)(n - 1) * rearrangeSticks(n - 1, k) % mod;
    ans += rearrangeSticks(n - 1, k - 1) % mod;
    return dp[n][k] = ans % mod;
}