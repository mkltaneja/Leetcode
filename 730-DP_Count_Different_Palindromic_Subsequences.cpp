
int mod = 1e9 + 7;
int countPalindromicSubsequences(string s)
{
    int n = s.size();
    unordered_map<char, int> m;

    vector<int> prev(n, -1);
    for (int i = 0; i < n; i++)
    {
        if (m.find(s[i]) != m.end())
            prev[i] = m[s[i]];
        m[s[i]] = i;
    }
    m.clear();

    vector<int> next(n, -1);
    for (int i = n - 1; i >= 0; i--)
    {
        if (m.find(s[i]) != m.end())
            next[i] = m[s[i]];
        m[s[i]] = i;
    }

    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            if (gap == 0)
            {
                dp[i][j] = 1;
                continue;
            }
            if (gap == 1)
            {
                dp[i][j] = 2;
                continue;
            }
            if (s[i] != s[j])
                dp[i][j] = (dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1]) % mod;
            else
            {
                int n = next[i];
                int p = prev[j];
                if (n > p)
                    dp[i][j] = (2 * dp[i + 1][j - 1] + 2) % mod;
                else if (n == p)
                    dp[i][j] = (2 * dp[i + 1][j - 1] + 1) % mod;
                else
                    dp[i][j] = (2 * dp[i + 1][j - 1] - dp[n + 1][p - 1]) % mod;
            }
            if (dp[i][j] < 0)
                dp[i][j] += mod;
        }
    }

    return dp[0][n - 1] % mod;
}