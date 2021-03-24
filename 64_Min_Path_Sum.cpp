
// APPROACH 1 (void type)
// TLE
void dfs(int i, int j, int n, int m, int sum, int &minsum, vector<vector<int>> &grid)
{
    if (i == n - 1 && j == m - 1)
    {
        minsum = min(minsum, sum + grid[i][j]);
        return;
    }
    if (i >= n || j >= m || i < 0 || j < 0)
        return;
    sum += grid[i][j];
    dfs(i + 1, j, n, m, sum, minsum, grid);
    dfs(i, j + 1, n, m, sum, minsum, grid);
    sum -= grid[i][j];
}

int minPathSum(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();
    int minsum = INT_MAX;
    // vector<vector<bool>> vis(n, vector<bool>(m, false));
    dfs(0, 0, n, m, 0, minsum, grid);
    return minsum;
}

// APPROACH 2 (DP --> Memoized)

int dfs(int i, int j, int n, int m, vector<vector<int>> &grid, vector<vector<int>> &dp)
{
    if (i == n - 1 && j == m - 1)
        return dp[i][j] = grid[i][j];
    if (i >= n || j >= m || i < 0 || j < 0)
        return dp[i][j] = INT_MAX;
    if (dp[i][j] != -1)
        return dp[i][j];
    int down = dfs(i + 1, j, n, m, grid, dp);
    int right = dfs(i, j + 1, n, m, grid, dp);

    return dp[i][j] = (min(down, right) + grid[i][j]);
}

int minPathSum(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    return dfs(0, 0, n, m, grid, dp);
}