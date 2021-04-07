
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