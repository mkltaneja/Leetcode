
// Time Complexity = O(n*m)
// Space Complexity = O(n*m)

class Solution {
public:
    int maxScore(vector<vector<int>>& grid) 
    {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> dp(n, vector<int>(m, INT_MIN));
        int ans = INT_MIN;
        for(int i = n-1; i >= 0; i--)
        {
            for(int j = m-1; j >= 0; j--)
            {
                if(i == n-1 && j == m-1)
                {
                    dp[i][j] = grid[i][j];
                    continue;
                }
                int right = j+1 < m? dp[i][j+1] : INT_MIN;
                int down = i+1 < n? dp[i+1][j] : INT_MIN;
                int mx = max(right, down);
                ans = max(ans, mx - grid[i][j]);
                dp[i][j] = max(mx, grid[i][j]);
            }
        }
        return ans;
    }
};
