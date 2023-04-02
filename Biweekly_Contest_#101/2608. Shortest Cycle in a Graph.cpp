class Solution {
public:
    int findShortestCycle(int n, vector<vector<int>>& edges) 
    {
        vector<vector<int>> gp(n);
        for(auto &e : edges)
        {
            gp[e[0]].push_back(e[1]);
            gp[e[1]].push_back(e[0]);
        }
        
        int ans = INT_MAX;
        for(int i = 0; i < n; i++)
        {
            vector<int> dist(n, -1);
            queue<pair<int,int>> que;
            que.push({i, -1});
            dist[i] = 0;
            
            while(!que.empty())
            {
                int u = que.front().first;
                int p = que.front().second;
                que.pop();
                
                for(int v : gp[u])
                {
                    if(dist[v] == -1)
                    {
                        dist[v] = dist[u] + 1;
                        que.push({v, u});
                    }
                    else if(v != p)
                        ans = min(ans, dist[v] + dist[u] + 1);
                }
            }
        }
        
        return ans == INT_MAX? -1 : ans;
    }
};
