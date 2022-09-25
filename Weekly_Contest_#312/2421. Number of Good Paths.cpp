class Solution {
public:
    
    #define f first
    #define s second
    
    vector<vector<int>> gp;
    vector<int> par;
    
    int findpar(int u)
    {
        return par[u] = par[u] == u? u : findpar(par[u]);
    }
    
    int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) 
    {
        int n = vals.size();
        int ans = n;
        gp.resize(n);
        par.resize(n);
        vector<pair<int,int>> vls(n);
        for(vector<int> e : edges)
        {
            gp[e[0]].push_back(e[1]);
            gp[e[1]].push_back(e[0]);
        }
        
        for(int i = 0; i < n; i++)
        {
            vls[i] = {vals[i], i};
            par[i] = i;
        }
        sort(vls.begin(), vls.end());
        
        for(int i = 0; i < n; )
        {
            int j = i;
            while(j < n && vls[j].f == vls[i].f)
            {
                for(int v : gp[vls[j].s])
                {
                    if(vals[v] > vls[j].f) continue;
                    
                    int p1 = findpar(vls[j].s);
                    int p2 = findpar(v);
                    if(p1 != p2) par[p1] = p2;
                }
                j++;
            }
            
            unordered_map<int,int> reach;
            for(int k = i; k < j; k++)
            {
                int p = findpar(vls[k].s);
                ans += reach[p]++;
            }
            i = j;
        }
        
        return ans;
    }
};
