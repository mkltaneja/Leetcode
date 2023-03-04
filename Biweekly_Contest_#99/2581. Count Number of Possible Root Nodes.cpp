class Solution {
public:
    
    #define f first
    #define s second
    
    vector<vector<int>> gp;
    set<pair<int,int>> st;
    set<pair<int,int>> gst;
    int ans = 0, kk = 0;
    
    void dfs1(int p, int u)
    {
        st.insert({p, u});
        
        for(int v : gp[u])
            if(v != p)
                dfs1(u, v);
    }
    
    void dfs2(int p, int u, int cnt)
    {
        st.erase({p, u});
        st.insert({u, p});
        
        int currcnt = gst.count({u, p}) - gst.count({p, u});
        cnt += currcnt;
        
        ans += cnt >= kk;
        
        for(int v : gp[u])
        {
            if(v != p)
                dfs2(u, v, cnt);
        }
        
        cnt -= currcnt;
        
        st.erase({u, p});
        st.insert({p, u});
    }
    
    int rootCount(vector<vector<int>>& edges, vector<vector<int>>& guesses, int k) 
    {
        kk = k;
        int n = 0;
        for(vector<int> &e : edges)
            n = max({n, e[0], e[1]});
        gp.resize(n+1);
        
        for(vector<int> &e : edges)
        {
            gp[e[0]].push_back(e[1]);
            gp[e[1]].push_back(e[0]);
        }
        for(vector<int> &g : guesses)
            gst.insert({g[0], g[1]});
        
        dfs1(-1, 0);
        int cnt = 0;
        for(auto p : st)
        {
            if(gst.count(p))
                cnt++;
        }
        
        dfs2(-1, 0, cnt);
        
        return ans;
    }
};
