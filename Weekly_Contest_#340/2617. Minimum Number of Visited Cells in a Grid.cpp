class Solution {
public:
    int minimumVisitedCells(vector<vector<int>>& grid) 
    {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> dp(n, vector<int> (m, INT_MAX));
        
        vector<set<int>> sx(n), sy(m);
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                sx[i].insert(j);
                sy[j].insert(i);
            }
        }
        
        queue<pair<int,int>> que;
        que.push({0, 0});
        dp[0][0] = 1;
        sx[0].erase(0);
        sy[0].erase(0);
        
        while(!que.empty())
        {
            auto [x, y] = que.front();
            que.pop();
            
            auto itr = sx[x].lower_bound(y);
            int yy = y + grid[x][y];
            while(itr != sx[x].end() && (*itr <= yy))
            {
                dp[x][*itr] = dp[x][y] + 1;
                que.push({x, *itr});
                
                int rem = *itr++;
                sx[x].erase(rem);
                sy[rem].erase(x);
            }
            
            itr = sy[y].lower_bound(x);
            int xx = x + grid[x][y];
            while(itr != sy[y].end() && (*itr <= xx))
            {
                dp[*itr][y] = dp[x][y] + 1;
                que.push({*itr, y});

                int rem = *itr++;
                sy[y].erase(rem);
                sx[rem].erase(y);
            }
        }
        
        return dp[n-1][m-1] == INT_MAX? -1 : dp[n-1][m-1];
    }
};
