// DAY 1 (1706. Where Will the Ball Fall)===========================================================================

vector<int> findBall(vector<vector<int>>& grid) 
{
    int n = grid.size(), m = grid[0].size();

    vector<int> ans(m, -1);
    for(int x = 0; x < m; x++)
    {
        int i = 0, j = x;
        while(i < n)
        {
            if(grid[i][j] == 1 && (j+1 == m || grid[i][j+1] == -1)) break;
            if(grid[i][j] == -1 && (j-1 == -1 || grid[i][j-1] == 1)) break;
            j += grid[i++][j];
        }
        if(i == n) ans[x] = j;
    }

    return ans;
}
