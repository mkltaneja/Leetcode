
void fillpals(int n, string &s, vector<vector<bool>> &dp)
{
    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            if (gap == 0)
                dp[i][j] = true;
            else if (gap == 1)
                dp[i][j] = (s[i] == s[j]);
            else
                dp[i][j] = ((s[i] == s[j]) && dp[i + 1][j - 1]);
            // cout<<dp[i][j]<<" ";
        }
        // cout<<endl;
    }
    // cout<<endl;
}

bool checkPartitioning(string s)
{
    int n = s.size();
    vector<vector<bool>> ispal(n, vector<bool>(n));
    fillpals(n, s, ispal);
    for (int i = 1; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (ispal[0][i - 1] && ispal[i][j - 1] && ispal[j][n - 1])
                return true;
    return false;
}