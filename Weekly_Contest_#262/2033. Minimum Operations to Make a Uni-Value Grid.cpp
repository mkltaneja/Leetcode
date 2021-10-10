
int minOperations(vector<vector<int>> &grid, int x)
{
    int ans = 0;
    int n = grid.size(), m = grid[0].size();
    vector<int> arr(n * m);
    int k = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            arr[k++] = grid[i][j];
    sort(arr.begin(), arr.end());

    int med = arr[(n * m) / 2];
    for (int i = 0; i < n * m; i++)
    {
        if (i && (arr[i] - arr[i - 1]) % x)
            return -1;
        ans += abs(arr[i] - med) / x;
    }

    return ans;
}