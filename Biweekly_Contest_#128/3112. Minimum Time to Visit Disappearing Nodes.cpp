
// Time Complexity = O(E + V (log(V)))
// Space Complexity = O(V)

class Solution {
public:
    vector<int> minimumTime(int n, vector<vector<int>>& edges, vector<int>& disappear) 
    {
        vector<int> minTime(n, INT_MAX);
        vector<vector<vector<int>>> gp(n);
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        for(vector<int> &e : edges)
        {
            int u = e[0], v = e[1], w = e[2];
            gp[u].push_back({v, w});
            gp[v].push_back({u, w});
        }
        pq.emplace(0, 0);
        minTime[0] = 0;
        
        while(!pq.empty())
        {
            int tsf = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            if(tsf != minTime[u]) continue;
            
            for(vector<int> &con : gp[u])
            {
                int v = con[0], t = con[1];
                int currTime = tsf + t;
                if(minTime[v] > currTime && currTime < disappear[v])
                {
                    minTime[v] = currTime;
                    pq.emplace(currTime, v);
                }
            }
        }
        for(int &x : minTime)
            if(x == INT_MAX)
                x = -1;
        return minTime;
    }
};
