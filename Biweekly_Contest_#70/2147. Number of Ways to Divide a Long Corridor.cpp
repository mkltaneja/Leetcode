
// APPROACH 1 (Naive) --> O(n)

int numberOfWays(string corridor)
{
    int s = 0;
    for (char c : corridor)
        s += c == 'S';
    if ((s & 1) || (s == 0))
        return 0;
    if (s == 2)
        return 1;

    long ans = 1, prev = ans;
    int mod = (int)(1e9 + 7);
    int x = 0;
    for (int i = 0; i <= corridor.size();)
    {
        if (x == 2)
        {
            int j = i;
            while (j < corridor.size() && corridor[j] == 'P')
                j++;
            ans = ((ans % mod) * (prev % mod)) % mod;
            prev = j - i + 1;
            i = j;
            x = 0;
        }
        else
        {
            if (i < corridor.size() && corridor[i] == 'S')
                x++;
            i++;
        }
    }
    return ans % mod;
}

// APPROACH 2 (DP) --> O(n)

int numberOfWays(string corridor)
{
    int n = corridor.size();
    vector<long> dp(n + 1), cnt(n + 1);
    dp[0] = cnt[0] = 1;
    int s = 0;
    int mod = (int)(1e9 + 7);
    for (int i = 1; i <= n; i++)
    {
        s += corridor[i - 1] == 'S';
        if (s >= 2)
            dp[i] = cnt[s - 2];
        cnt[s] = ((cnt[s] % mod) + (dp[i] % mod)) % mod;
    }
    return dp[n];
}