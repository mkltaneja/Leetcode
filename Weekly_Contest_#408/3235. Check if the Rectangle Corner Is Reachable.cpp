
// Time Complexity = O(n^2)
// Space Complexity = O(n)

class Solution {
public:
    
    class DSU
    {
        public:
        int n;
        vector<int> par, parSize;
        DSU(int n)
        {
            this->n = n;
            this->par.resize(n);
            this->parSize.assign(n, 1);
            for(int node = 0; node < n; node++)
                par[node] = node;
        }
        
        int findPar(int node)
        {
            return par[node] = par[node] == node? node : findPar(par[node]);
        }
        
        void merge(int node1, int node2)
        {
            int par1 = findPar(node1);
            int par2 = findPar(node2);
            if(par1 == par2)
                return;
            
            if(parSize[par2] > parSize[par1])
                swap(par1, par2);
            
            parSize[par1] += parSize[par2];
            par[par2] = par1;
        }
    };
    
    bool areIntersecting(int x1, int y1, int r1, int x2, int y2, int r2)
    {
        long long centerDist = 1LL * (x1 - x2) * (x1 - x2) + 1ll * (y1 - y2) * (y1 - y2);
        long long rSquare = 1LL * (r1 + r2) * (r1 + r2);
        
        return centerDist <= rSquare;
    }
    
    bool canReachCorner(int X, int Y, vector<vector<int>>& circles)
    {
        int n = circles.size();
        DSU dsu(n+4);
        const int LEFT = n;
        const int RIGHT = n+1;
        const int TOP = n+2;
        const int BOTTOM = n+3;
        
        for(int i = 0; i < n; i++)
        {
            int x = circles[i][0], y = circles[i][1], r = circles[i][2];
            if(x - r <= 0)
                dsu.merge(i, LEFT);
            if(y - r <= 0)
                dsu.merge(i, BOTTOM);
            if(x + r >= X)
                dsu.merge(i, RIGHT);
            if(y + r >= Y)
                dsu.merge(i, TOP);
            
            for(int j = i+1; j < n; j++)
            {
                int x2 = circles[j][0], y2 = circles[j][1], r2 = circles[j][2];
                if(areIntersecting(x, y, r, x2, y2, r2))
                    dsu.merge(i, j);
            }
        }
        
        if(dsu.findPar(LEFT) == dsu.findPar(BOTTOM) || dsu.findPar(TOP) == dsu.findPar(RIGHT) || dsu.findPar(TOP) == dsu.findPar(BOTTOM) || dsu.findPar(LEFT) == dsu.findPar(RIGHT))
            return false;
        return true;
    }
};
