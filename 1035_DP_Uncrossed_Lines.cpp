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
// 