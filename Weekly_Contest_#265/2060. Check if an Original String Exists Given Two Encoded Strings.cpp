
int dp[45][45][2005];

bool dfs(int i, int j, int k, int n, int m, string &s, string &t)
{
    int kk = k + 1000;

    if (dp[i][j][kk] != -1)
        return dp[i][j][kk];

    if (i == s.size() && j == t.size())
        return dp[i][j][kk] = (k == 0);

    if (k == 0 && isalpha(s[i]) && isalpha(t[j]))
        return dp[i][j][kk] = ((s[i] == t[j]) && dfs(i + 1, j + 1, k, n, m, s, t));
    if (k <= 0)
    {
        if (j == m)
            return dp[i][j][kk] = false;
        if (isalpha(t[j]))
            return dp[i][j][kk] = dfs(i, j + 1, k + 1, n, m, s, t);

        int x = 0;
        for (int p = j; p < m && isdigit(t[p]); p++)
        {
            x = x * 10 + (t[p] - '0');
            if (dfs(i, p + 1, k + x, n, m, s, t))
                return dp[i][j][kk] = true;
        }
        return dp[i][j][kk] = false;
    }
    else
    {
        if (i == n)
            return dp[i][j][kk] = false;
        if (isalpha(s[i]))
            return dp[i][j][kk] = dfs(i + 1, j, k - 1, n, m, s, t);

        int x = 0;
        for (int p = i; p < n && isdigit(s[p]); p++)
        {
            x = x * 10 + (s[p] - '0');
            if (dfs(p + 1, j, k - x, n, m, s, t))
                return dp[i][j][kk] = true;
        }
        return dp[i][j][kk] = false;
    }
}

bool possiblyEquals(string s1, string s2)
{
    memset(dp, -1, sizeof(dp));
    return dfs(0, 0, 0, s1.size(), s2.size(), s1, s2);
}