
// Time Complexity = O(E*log(V))
// Space Complexity = O(E + V)

class Solution {
public:
    
    #define f first
    #define s second
    #define ll long long
    
    vector<ll> dijikstra(int src, int n, vector<vector<vector<int>>> &gp)
    {
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
        vector<ll> md(n, INT_MAX);
        pq.emplace(0, src);
        md[src] = 0;
        while(!pq.empty())
        {
            int u = pq.top().s;
            ll wsf = pq.top().f;
            pq.pop();
            
            if(wsf != md[u])
                continue;
            
            for(vector<int> &con : gp[u])
            {
                int v = con[0], w = con[1];
                if(wsf + w < md[v])
                {
                    md[v] = wsf + w;
                    pq.emplace(wsf + w, v);
                }
            }
        }
        return md;
    }

    vector<bool> findAnswer(int n, vector<vector<int>>& edges) 
    {
        int m = edges.size();
        vector<bool> isInc(m, false);
        int idx = 0;
        vector<vector<vector<int>>> gp(n);
        for(vector<int> &e : edges)
        {
            int u = e[0], v = e[1], w = e[2];
            gp[u].push_back({v, w});
            gp[v].push_back({u, w});
        }
        
        vector<ll> md0 = dijikstra(0, n, gp);
        vector<ll> mdn = dijikstra(n-1, n, gp);
        ll minDist = md0[n-1];
        
        for(vector<int> &e : edges)
        {
            int u = e[0], v = e[1];
            ll w = e[2];
            if((md0[u] + w + mdn[v] == minDist) || (md0[v] + w + mdn[u] == minDist))
                isInc[idx] = true;
            idx++;
        }
        
        return isInc;
    }
};
