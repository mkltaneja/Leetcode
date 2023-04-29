class Solution {
public:
    
    int dfs(int i, int j, int n, int m, vector<vector<int>>& grid)
    {
        if(i == -1 || j == -1 || i == n || j == m || grid[i][j] == 0)
            return 0;
        
        int x = grid[i][j];
        grid[i][j] = 0;
        return x + dfs(i+1, j, n, m, grid)
            + dfs(i, j+1, n, m, grid)
            + dfs(i-1, j, n, m, grid)
            + dfs(i, j-1, n, m, grid);
    }
    
    int findMaxFish(vector<vector<int>>& grid) 
    {
        int n = grid.size(), m = grid[0].size();
        int ans = 0;
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                if(grid[i][j] == 0) continue;
                ans = max(ans, dfs(i, j, n, m, grid));
            }
        }
        
        return ans;
    }
};
