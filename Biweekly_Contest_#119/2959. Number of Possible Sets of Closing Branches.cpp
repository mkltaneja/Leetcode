class Solution {
public:
    int numberOfSets(int n, int maxDistance, vector<vector<int>>& roads) 
    {
        vector<vector<int>> gp(n, vector<int> (n, INT_MAX));
        int sets = 0;
        for(vector<int> &e : roads)
        {
            gp[e[0]][e[1]] = min(gp[e[0]][e[1]], e[2]);
            gp[e[1]][e[0]] = min(gp[e[1]][e[0]], e[2]);
        }
        
        for(int r = 0; r < (1 << n); r++)
        {
            bool isValid = true;
            for(int i = 0; i < n; i++)
            {
                if((r >> i) & 1) continue;
                
                priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
                pq.push({0, i});
                vector<int> minDist(n, INT_MAX);
                minDist[i] = 0;
                
                while(!pq.empty())
                {
                    int md = pq.top().first;
                    int u = pq.top().second;
                    pq.pop();
                    
                    for(int v = 0; v < gp[u].size(); v++)
                    {
                        if(((r >> v) & 1) || gp[u][v] == INT_MAX || minDist[v] <= md + gp[u][v]) continue;
                        
                        minDist[v] = md + gp[u][v];
                        pq.push({md + gp[u][v], v});
                    }
                }
                
                int j = 0;
                for(int x : minDist)
                {
                    if(((r >> j) & 1 ^ 1) && x > maxDistance)
                    {
                        isValid = false;
                        break;
                    }
                    j++;
                }
            }
            if(isValid) sets++;
        }
        
        return sets;
    }
};

// 3
// 5
// [[0,1,2],[1,2,10],[0,2,10]]
// 3
// 5
// [[0,1,20],[0,1,10],[1,2,2],[0,2,2]]
// 1
// 10
// []
// 3
// 3
// [[2,0,14],[1,0,15],[1,0,7]]
