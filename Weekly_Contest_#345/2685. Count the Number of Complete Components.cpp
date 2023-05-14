class Solution {
public:
    
    #define f first
    #define s second
    class DSU 
    {
        public:
        vector<int> par;
        vector<int> nodesCnt;
        vector<int> edgesCnt;
        
        DSU(int n)
        {
            par.resize(n);
            for(int i = 0; i < n; i++)
                par[i] = i;
            nodesCnt.assign(n, 1);
            edgesCnt.assign(n, 0);
        }
        
        int findPar(int u)
        {
            return par[u] = par[u] == u? u : findPar(par[u]);
        }
        
        void merge(int u, int v)
        {
            int pu = findPar(u);
            int pv = findPar(v);
            
            if(pu != pv)
                edgesCnt[pu] += edgesCnt[pv] + 1;
            else 
            {
                edgesCnt[pu] += 1;
                return;
            }
            
            par[pv] = pu;
            nodesCnt[pu] += nodesCnt[pv];
        }
    };
    
    int countCompleteComponents(int n, vector<vector<int>>& edges) 
    {
        DSU dsu(n);
        
        for(auto e : edges)
            dsu.merge(e[0], e[1]);
        
        int ans = 0;
        for(int i = 0; i < n; i++)
        {
            int pi = dsu.findPar(i);
            if(pi != i) continue;
            int nc = dsu.nodesCnt[pi], ec = dsu.edgesCnt[pi];
            ans += (nc*(nc-1))/2 == ec;
        }
        return ans;
    }
};
