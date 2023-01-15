class Solution {
public:
    
    #define f first
    #define s second
    #define ll long long
    
    ll ans = 0;
    vector<ll> childMax;
    vector<int> pr;
    vector<vector<int>> graph;
    
    ll dfs1(int p, int u)
    {
        for(int v : graph[u])
        {
            if(v == p) continue;
            childMax[u] = max(childMax[u], dfs1(u, v));
        }
        
        return childMax[u] = childMax[u] + pr[u];
    }
    
    void dfs2(int p, int u, ll parMax)
    {
        ans = max(ans, max(childMax[u], parMax + pr[u]) - pr[u]);
        ll max1 = parMax + pr[u], max2 = parMax + pr[u];
        for(int v : graph[u])
        {
            if(v == p) continue;
            ll currMax = childMax[v] + pr[u];
            if(currMax > max1)
            {
                max2 = max1;
                max1 = currMax;
            }
            else max2 = max(max2, currMax);
        }
        
        for(int v : graph[u])
        {
            if(v == p) continue;
            if(childMax[v] + pr[u] == max1)
                dfs2(u, v, max2);
            else dfs2(u, v, max1);
        }
    }
    
    long long maxOutput(int n, vector<vector<int>>& edges, vector<int>& price) 
    {
        pr = price;
        childMax.assign(n, 0);
        graph.resize(n);
        for(vector<int> &e : edges)
        {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }
        
        dfs1(-1, 0);
        dfs2(-1, 0, 0);
        
        return ans;
    }
};
