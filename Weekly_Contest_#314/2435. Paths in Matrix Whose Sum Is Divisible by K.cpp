class Solution {
public:
    
    int mod = 1e9 + 7;
    
    int numberOfPaths(vector<vector<int>>& grid, int k) 
    {
        int n = grid.size(), m = grid[0].size();
        vector<vector<vector<long>>> dp(n, vector<vector<long>> (m, vector<long> (k+1, 0)));
        dp[n-1][m-1][grid[n-1][m-1] % k] = 1;
        for(int i = n-1; i >= 0; i--)
        {
            for(int j = m-1; j >= 0; j--)
            {
                if(i == n-1 && j == m-1) continue;
                for(int x = 0; x < k; x++)
                {
                    if(i+1 < n && dp[i+1][j][x])
                        dp[i][j][(grid[i][j] % k + x) % k] += dp[i+1][j][x] % mod;
                    if(j+1 < m && dp[i][j+1][x])
                        dp[i][j][(grid[i][j] % k + x) % k] += dp[i][j+1][x] % mod;
                }
            }
        }
        return dp[0][0][0] % mod;
    }
};
