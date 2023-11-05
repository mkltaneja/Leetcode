class Solution {
public:
    
    #define ll long long
    
    ll dfs(int u, int p, vector<vector<int>> &gp, vector<int> &values)
    {
        ll sum = 0;
        for(int v : gp[u])
        {
            if(v == p) continue;
            sum += dfs(v, u, gp, values);
        }
        
        return sum? min(sum, (ll)values[u]) : (ll)values[u];
    }
    
    long long maximumScoreAfterOperations(vector<vector<int>>& edges, vector<int>& values) 
    {
        int n = values.size();
        vector<vector<int>> gp(n);
        for(vector<int> &e : edges)
        {
            gp[e[0]].push_back(e[1]);
            gp[e[1]].push_back(e[0]);
        }
        
        ll totSum = 0;
        for(int x : values)
            totSum += (ll)x;
        ll minSum = dfs(0, -1, gp, values);
        
        return totSum - minSum;
    }
};
