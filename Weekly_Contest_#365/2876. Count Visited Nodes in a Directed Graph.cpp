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
