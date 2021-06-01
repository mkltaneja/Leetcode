 int islandPerimeter(vector<vector<int>>& grid) 
{
    int totalOnes = 0;
    int commonRegions = 0;
    
    for(int i=0;i<grid.size();i++)
    {
        for(int j=0;j<grid[0].size();j++)
        {
            if(grid[i][j] == 1)
            {
                totalOnes++;
                if(i+1 < grid.size() && grid[i+1][j] == 1)
                    commonRegions++;
                if(j+1 < grid[0].size() && grid[i][j+1] == 1)
                    commonRegions++;
            }
        }
    }
    
    return (4*totalOnes - 2*commonRegions);
}