
int longestPalindrome(string a, string b)
{
    int n = a.size(), m = b.size();
    string s = a + b;
    int maxlen = 0;
    vector<vector<int>> dp(n + m, vector<int>(n + m, 0));
    for (int gap = 0; gap < n + m; gap++)
    {
        for (int i = 0, j = gap; j < n + m; i++, j++)
        {
            if (i == j)
                dp[i][j] = 1;
            else if (s[i] == s[j])
            {
                dp[i][j] = dp[i + 1][j - 1] + 2;
                if (i < n && j >= n)
                    maxlen = max(maxlen, dp[i][j]);
            }
            else
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
        }
    }
    return maxlen;
}