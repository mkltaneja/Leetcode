
// Method 1 (recusrsion)
// TLE
int lcs_rec(int i, int j, int n, int m, string s, string t)
{
    if (i == n || j == m)
        return 0;
    int ans = 0;
    if (s[i] == t[j])
        ans = lcs_rec(i + 1, j + 1, n, m, s, t) + 1;
    else
        ans = max(lcs_rec(i + 1, j, n, m, s, t), lcs_rec(i, j + 1, n, m, s, t));
    return ans;
}

int longestCommonSubsequence(string text1, string text2)
{
    return lcs_rec(0, 0, text1.size(), text2.size(), text1, text2);
}

// Method 2 (memoization)
// TLE
int lcs_rec(int i, int j, int n, int m, string s, string t, vector<vector<int>> &dp)
{
    if (i == n || j == m)
        return 0;

    if (dp[i][j] != 0)
        return dp[i][j];

    int ans = 0;
    if (s[i] == t[j])
        ans = lcs_rec(i + 1, j + 1, n, m, s, t, dp) + 1;
    else
        ans = max(lcs_rec(i + 1, j, n, m, s, t, dp), lcs_rec(i, j + 1, n, m, s, t, dp));
    return dp[i][j] = ans;
}

int longestCommonSubsequence(string text1, string text2)
{
    int n = text1.size();
    int m = text2.size();
    vector<vector<int>> dp(n, vector<int>(m, 0));
    return lcs_rec(0, 0, text1.size(), text2.size(), text1, text2, dp);
}

// Method 3 (Tabulation)
// AC
int longestCommonSubsequence(string text1, string text2)
{
    int n = text1.size();
    int m = text2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = m - 1; j >= 0; j--)
        {
            if (text1[i] == text2[j])
                dp[i][j] = dp[i + 1][j + 1] + 1;
            else
                dp[i][j] = max(dp[i + 1][j], dp[i][j + 1]);
        }
    }
    return dp[0][0];
}