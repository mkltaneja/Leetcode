int maxAreaOfIsland_dfs(int r, int c, int n, int m, vector<vector<int>>& grid)
{
    if(grid[r][c] != 1)
        return 0;
    
    int count = 0;
    
    grid[r][c] = 0;
    
    if(r+1 < n)
        count += maxAreaOfIsland_dfs(r+1,c,n,m,grid);
    if(c+1 < m)
        count += maxAreaOfIsland_dfs(r,c+1,n,m,grid);
    if(r-1 >= 0)
        count += maxAreaOfIsland_dfs(r-1,c,n,m,grid);
    if(c-1 >= 0)
        count += maxAreaOfIsland_dfs(r,c-1,n,m,grid);
    
    return count+1;
}

int maxAreaOfIsland(vector<vector<int>>& grid) 
{
    int n = grid.size();
    int m = grid[0].size();
    int maxSize = 0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(grid[i][j] == 1)
                maxSize = max(maxSize,maxAreaOfIsland_dfs(i,j,n,m,grid));
        }
    }
    return maxSize;
}