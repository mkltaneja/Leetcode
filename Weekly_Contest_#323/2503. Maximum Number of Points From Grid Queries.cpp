class Solution {
public:
    
    #define f first
    #define s second
    #define MX 1000005
    
    vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries) 
    {
        int n = grid.size(), m = grid[0].size(), k = queries.size();
        vector<vector<int>> vis(n, vector<int>(m, 0));
        vector<int> cnt(MX, 0);
        
        int dir[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
        
        priority_queue<pair<int,pair<int,int>>, vector<pair<int,pair<int,int>>>, greater<pair<int,pair<int,int>>>> pq;
        pq.push({grid[0][0], {0, 0}});
        vis[0][0] = 1;
        
        int currMax = 0;
        
        while(!pq.empty())
        {
            int x = pq.top().f;
            int i = pq.top().s.f;
            int j = pq.top().s.s;
            pq.pop();
            
            currMax = max(currMax, x+1);
            cnt[currMax]++;
            
            for(int d = 0; d < 4; d++)
            {
                int x = i + dir[d][0], y = j + dir[d][1];
                if(x >= 0 && x < n && y >= 0 && y < m && !vis[x][y])
                {
                    vis[x][y] = 1;
                    pq.push({grid[x][y], {x, y}});
                }
            }
        }
        
        int prevCnt = 0;
        for(int i = 0; i < MX; i++)
        {
            prevCnt += cnt[i];
            cnt[i] = prevCnt;
        }
        
        vector<int> ans(k);
        for(int i = 0; i < k; i++)
            ans[i] = cnt[queries[i]];
        
        return ans;
    }
};
