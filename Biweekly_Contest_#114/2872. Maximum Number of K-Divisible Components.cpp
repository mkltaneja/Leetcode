class Solution {
public:
    
    #define ll long long
    
    int ans = 0;
    
    ll dfs(int u, int p, vector<vector<int>> &gp, vector<int> &values, int k)
    {
        ll sum = values[u];
        for(int v : gp[u])
        {
            if(v != p)
                sum += dfs(v, u, gp, values, k);
        }
        if(sum % k == 0)
        {
            sum = 0;
            ans++;
        }
        return sum;
    }
    
    int maxKDivisibleComponents(int n, vector<vector<int>>& edges, vector<int>& values, int k) 
    {
        vector<vector<int>> gp(n);
        for(vector<int> &e : edges)
        {
            gp[e[0]].push_back(e[1]);
            gp[e[1]].push_back(e[0]);
        }
        dfs(0, -1, gp, values, k);
        return ans;
    }
};
