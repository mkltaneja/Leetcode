class Solution {
public:
    
    vector<vector<int>> gp;
    vector<int> mp;
    vector<int> pr;
    int dfs(int p, int u, int dest)
    {
        if(u == dest) 
        {
            mp[u]++;
            return 1;
        }
        
        for(int v : gp[u])
        {
            if(v != p)
            {
                int x = dfs(u, v, dest);
                if(x == 1)
                {
                    mp[u]++;
                    return 1;
                }
            }
        }
        
        return 0;
    }
    
    void min_dfs(int p, int u, vector<vector<int>> &dp)
    {
        dp[u][0] = 0;
        dp[u][1] = pr[u];
        
        for(int v : gp[u])
        {
            if(v == p) continue;
            min_dfs(u, v, dp);
            dp[u][0] += max(dp[v][0], dp[v][1]);
            dp[u][1] += dp[v][0];
        }
    }
    
    int minimumTotalPrice(int n, vector<vector<int>>& edges, vector<int>& price, vector<vector<int>>& trips) 
    {
        gp.resize(n);
        mp.resize(n);
        pr = price;
        for(auto &e : edges)
        {
            gp[e[0]].push_back(e[1]);
            gp[e[1]].push_back(e[0]);
        }
        
        for(vector<int> &t : trips)
            dfs(-1, t[0], t[1]);
        
        int ans = 0;
        for(int i = 0; i < n; i++)
        {
            pr[i] *= mp[i];
            ans += pr[i];
        }
        
        vector<vector<int>> dp(n, vector<int> (2, 0));
        min_dfs(-1, 0, dp);
        
        return ans - (max(dp[0][0], dp[0][1]) / 2);
    }
};
