
// APPROACH 1 (Fill every cycle first, then nodes connected to it) --> Time = O(2*n*log(n) + n), Space = O(3*n)

class Solution {
public:
    
    map<int,int> seen;
    set<int> vis;
    int cc = 0, cp = -1;
    vector<int> ans;
    void cycleCount(int u, int cnt, vector<int> &e)
    {
        if(vis.count(u))
            return;
        if(seen.count(u))
        {
            cc = cnt - seen[u];
            cp = u;
            return;
        }
        seen[u] = cnt;
        cycleCount(e[u], cnt+1, e);
        vis.insert(u);
    }
    
    void fillCycle(int u, vector<int> &e)
    {
        if(ans[u] != -1)
            return;
        ans[u] = cc;
        fillCycle(e[u], e);
    }
    
    int dfs(int u, vector<int> &e, vector<int> &ans)
    {
        if(ans[u] != -1)
            return ans[u];
        int ret = dfs(e[u], e, ans);
        return ans[u] = ret + 1;
    }
    
    vector<int> countVisitedNodes(vector<int>& edges) 
    {
        int n = edges.size();
        ans.assign(n, -1);
        for(int i = 0; i < n; i++)
        {
            cycleCount(i, 0, edges);
            if(cp != -1)
                fillCycle(cp, edges);
            
            cp = -1, cc = 0;
            seen.clear();
        }
        
        
        for(int i = 0; i < n; i++)
            dfs(i, edges, ans);
        
        return ans;
    }
};

// APPROACH 2 (Similar Approach as Approach 1, but in an optimized way -- Collected all the nodes in the topological order, then filled them accordingly) --> Time = O(4*n), Space = O(3*n) --> [OPTIMIZED]

class Solution {
public:
    
    vector<int> topologicalNodes;
    void dfs(int u, vector<int> &edges, vector<int> &vis)
    {
        if(vis[u]) return;
        
        vis[u] = 1;
        dfs(edges[u], edges, vis);
        topologicalNodes.push_back(u);
    }
    
    vector<int> countVisitedNodes(vector<int>& edges) 
    {
        int n = edges.size();
        vector<int> vis(n, 0), ans(n, 0);
        for(int i = 0; i < n; i++)
            if(!vis[i])
                dfs(i, edges, vis);
        
        for(int u : topologicalNodes)
        {
            if(ans[u]) continue;
            
            ans[u] = 1;
            int v = edges[u];
            if(ans[v])
            {
                ans[u] += ans[v];
                continue;
            }
            
            int cnt = 1;
            while(v != u)
            {
                cnt++;
                v = edges[v];
            }
            ans[u] = cnt;
            v = edges[u];
            while(v != u)
            {
                ans[v] = cnt;
                v = edges[v];
            }
        }
        
        return ans;
    }
};
