class Solution {
public:
    
    const int MOD = 12345;
    vector<vector<int>> constructProductMatrix(vector<vector<int>>& grid) 
    {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> ans(n, vector<int>(m, 1));
        long prod = 1;
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                (ans[i][j] *= prod) %= MOD;
                (prod *= grid[i][j]) %= MOD;
            }
        }
        prod = 1;
        for(int i = n-1; i >= 0; i--)
        {
            for(int j = m-1; j >= 0; j--)
            {
                (ans[i][j] *= prod) %= MOD;
                (prod *= grid[i][j]) %= MOD;
            }
        }
        
        return ans;
    }
};
