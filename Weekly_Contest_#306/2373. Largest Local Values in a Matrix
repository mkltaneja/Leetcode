
vector<vector<int>> largestLocal(vector<vector<int>>& grid) 
{
    int n = grid.size();
    vector<vector<int>> ans(n-2, vector<int>(n-2));

    for(int i = 0; i+2 < n; i++)
    {
        for(int j = 0; j+2 < n; j++)
        {
            for(int ii = i; ii < i+3; ii++)
                for(int jj = j; jj < j+3; jj++)
                    ans[i][j] = max(ans[i][j], grid[ii][jj]);
        }
    }
    return ans;
}
