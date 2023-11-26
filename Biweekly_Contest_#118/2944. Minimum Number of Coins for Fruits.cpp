class Solution {
public:
    
    int dfs(int i, int prev, int n, vector<int>& prices, vector<vector<int>>& dp)
    {
        if(i == n) return 0;
        if(dp[i][prev] != -1)
            return dp[i][prev];
        
        int ans = INT_MAX;
        ans = min(ans, dfs(i+1, i+1, n, prices, dp) + prices[i]);
        if(prev)
            ans = min(ans, dfs(i+1, prev-1, n, prices, dp));
        return dp[i][prev] = ans;
    }
    
    int minimumCoins(vector<int>& prices) 
    {
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));
        return dfs(1, 1, n, prices, dp) + prices[0];
    }
};
