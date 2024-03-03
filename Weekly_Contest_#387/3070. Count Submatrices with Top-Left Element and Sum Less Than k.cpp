
// Time Complexity = O(n*m)
// Space Complexity = O(1)

class Solution {
public:
    int countSubmatrices(vector<vector<int>>& grid, int k) 
    {
        int n = grid.size(), m = grid[0].size();
        int ans = 0;
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                grid[i][j] += (i? grid[i-1][j] : 0) + (j? grid[i][j-1] : 0) - ((i && j)? grid[i-1][j-1] : 0);
                if(grid[i][j] <= k) ans++;
            }
        }
        return ans;
    }
};
