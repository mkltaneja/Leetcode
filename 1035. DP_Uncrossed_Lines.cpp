// Method 1 (memoized recursion)
// TLE

int lcs_rec(int i, int j, int n, int m, vector<int> &s, vector<int> &t, vector<vector<int>> &dp)
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

int maxUncrossedLines(vector<int> &A, vector<int> &B)
{
    int n = A.size();
    int m = B.size();
    vector<vector<int>> dp(n, vector<int>(m, 0));
    return lcs_rec(0, 0, n, m, A, B, dp);
}

// Method 2 (Tabulation)
// Passed

int lcs_rec(int i, int j, int n, int m, vector<int> &s, vector<int> &t, vector<vector<int>> &dp)
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

int maxUncrossedLines(vector<int> &A, vector<int> &B)
{
    int n = A.size();
    int m = B.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = m - 1; j >= 0; j--)
        {
            if (A[i] == B[j])
                dp[i][j] = dp[i + 1][j + 1] + 1;
            else
                dp[i][j] = max(dp[i + 1][j], dp[i][j + 1]);
        }
    }
    return dp[0][0];
}