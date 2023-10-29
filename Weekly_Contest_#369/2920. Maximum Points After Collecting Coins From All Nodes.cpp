class Solution {
public:
    
    int dfs(int p, int u, int d, int k, vector<int> &coins, vector<vector<int>> &gp, vector<vector<int>> &dp)
    {
        if(d > 14) return INT_MIN;
        
        if(dp[u][d] != -1) return dp[u][d];
        
        int actCoins = coins[u];
        for(int i = 0; i < d; i++)
            actCoins >>= 1;
        
        long way1 = actCoins - k;
        long way2 = actCoins / 2;
        for(int v : gp[u])
        {
            if(v == p) continue;
            way1 += dfs(u, v, d, k, coins, gp, dp);
        }
        
        for(int v : gp[u])
        {
            if(v == p) continue;
            way2 += dfs(u, v, d+1, k, coins, gp, dp);
        }
        
        return dp[u][d] = max(way1, way2);
    }
    
    int maximumPoints(vector<vector<int>>& edges, vector<int>& coins, int k) 
    {
        int n = coins.size();
        vector<vector<int>> gp(n);
        vector<vector<int>> dp(n, vector<int>(20, -1));
        for(vector<int> &e : edges)
        {
            gp[e[0]].push_back(e[1]);
            gp[e[1]].push_back(e[0]);
        }
        
        return dfs(-1, 0, 0, k, coins, gp, dp);
    }
};
