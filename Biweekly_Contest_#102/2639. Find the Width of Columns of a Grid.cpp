class Solution {
public:
    vector<int> findColumnWidth(vector<vector<int>>& grid) 
    {
        int n = grid.size(), m = grid[0].size();
        vector<int> ans(m);
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < n; j++)
                ans[i] = max(ans[i], (int)to_string(grid[j][i]).size());
        }
        
        return ans;
    }
};
