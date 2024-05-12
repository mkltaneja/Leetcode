
// Time Complexity = O(n*m)
// Space Complexity = O(1)

class Solution {
public:
    bool satisfiesConditions(vector<vector<int>>& grid) 
    {
        int n = grid.size(), m = grid[0].size();
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                if((j+1 < m && grid[i][j] == grid[i][j+1]) || (i+1 < n && grid[i][j] != grid[i+1][j]))
                    return false;
        return true;
    }
};
