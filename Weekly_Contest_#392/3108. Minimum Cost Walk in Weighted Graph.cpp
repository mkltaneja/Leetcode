
// Time Complexity = O(n)
// Space Complexity = O(n)

class Solution {
public:
    
    class DSU
    {
        public:
        int n;
        vector<int> par;
        vector<int> psize;
        vector<int> nd;
        DSU(int n)
        {
            this->n = n;
            this->par.resize(n);
            this->psize.assign(n, 1);
            this->nd.assign(n, ((1 << 30) - 1));
            
            for(int i = 0; i < n; i++)
                this->par[i] = i;
        }
        
        int findPar(int u)
        {
            return par[u] = (par[u] == u)? u : findPar(par[u]);
        }
        
        void merge(int u, int v, int w)
        {
            int p1 = findPar(u);
            int p2 = findPar(v);
            if(p1 != p2)
            {
                if(psize[p2] > psize[p1])
                    swap(p1, p2);
                psize[p1] += psize[p2];
                par[p2] = p1;
            }
            nd[p1] &= nd[p2] & w;
        }
    };
    
    vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& query) 
    {
        DSU dsu(n+1);
        vector<int> ans;
        for(vector<int> &e : edges)
        {
            int u = e[0], v = e[1], w = e[2];
            dsu.merge(u, v, w);
        }
        for(vector<int> &e : query)
        {
            int u = e[0], v = e[1];
            int pu = dsu.findPar(u);
            int pv = dsu.findPar(v);
            if(pu != pv)
                ans.push_back(-1);
            else
            {
                if(u == v)
                    ans.push_back(0);
                else
                    ans.push_back(dsu.nd[pu]);
            }
        }
        
        return ans;
    }
};
