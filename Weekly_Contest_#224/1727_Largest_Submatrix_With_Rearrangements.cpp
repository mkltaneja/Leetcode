
int largestSubmatrix(vector<vector<int>> &matrix)
{
    int n = matrix.size(), m = matrix[0].size();
    vector<vector<int>> consec(n + 1, vector<int>(m, 0));
    for (int i = n - 1; i >= 0; i--)
        for (int j = 0; j < m; j++)
            if (matrix[i][j])
                consec[i][j] = consec[i + 1][j] + 1;
    // for(int i = 0; i < n; i++)
    // {
    //     for(int j = 0; j < m; j++)
    //         cout<<consec[i][j]<<" ";
    //     cout<<endl;
    // }
    cout << endl;
    int ans = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        sort(consec[i].begin(), consec[i].end());
        for (int j = 1; j <= m; j++)
            ans = max(ans, consec[i][m - j] * j);
    }
    return ans;
}