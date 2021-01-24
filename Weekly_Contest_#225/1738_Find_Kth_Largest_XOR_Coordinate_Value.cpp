
int kthLargestValue(vector<vector<int>> &matrix, int k)
{
    int n = matrix.size(), m = matrix[0].size();
    int xord = 0;
    priority_queue<int> pq;
    vector<vector<int>> dp(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int up = 0, left = 0, diag = 0;
            if (i > 0)
                up = dp[i - 1][j];
            if (j > 0)
                left = dp[i][j - 1];
            if (i > 0 && j > 0)
                diag = dp[i - 1][j - 1];
            dp[i][j] = up ^ left ^ matrix[i][j] ^ diag;
            // cout<<dp[i][j]<<" ";
            pq.push(dp[i][j]);
        }
        // cout<<endl;
    }
    // cout<<endl;
    while (--k)
        pq.pop();
    return pq.top();
}