
int lps(int i, int j, string &s, vector<vector<int>> &dp)
{
    if(i == j) return dp[i][j] = 1;
    if(i > j) return dp[i][j] = 0;
    if(dp[i][j] != -1) return dp[i][j];
    int ans = 0;
    if(s[i] == s[j]) ans = lps(i+1, j-1, s, dp)+2;
    else ans = max(lps(i+1, j, s, dp), lps(i, j-1, s, dp));
    return dp[i][j] = ans;
}

int longestPalindromeSubseq(string s) 
{
    vector<vector<int>> dp(s.size(), vector<int>(s.size(),-1));
    return lps(0, s.size()-1, s, dp);
}

// METHOD 2 --> (TABULATION)

int lps(int n, string &s, vector<vector<int>> &dp)
{
    for(int gap = 0; gap < n; gap++)
    {
        for(int i = 0, j = gap; j < n; i++, j++)
        {
            if(gap == 0)
            {
                dp[i][j] = 1;
                continue;
            }
            if(s[i] == s[j])
                dp[i][j] = dp[i+1][j-1] + 2;
            else
                dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
        }
    }
    return dp[0][n-1];
}

int longestPalindromeSubseq(string s) 
{
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    return lps(n, s, dp);
}