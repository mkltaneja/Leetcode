// DAY 1 (Longest Common Subsequence)============================================================

int longestCommonSubsequence(string text1, string text2)
{
    int n = text1.size(), m = text2.size();
    int ans = 0;
    vector<vector<int>> dp(n, vector<int>(m, 0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int im1 = i ? dp[i - 1][j] : 0;
            int jm1 = j ? dp[i][j - 1] : 0;
            int ijm1 = (i && j) ? dp[i - 1][j - 1] : 0;

            dp[i][j] = (text1[i] == text2[j]) ? max({ijm1 + 1, im1, jm1}) : max(im1, jm1);
            ans = max(ans, dp[i][j]);
        }
    }
    return ans;
}