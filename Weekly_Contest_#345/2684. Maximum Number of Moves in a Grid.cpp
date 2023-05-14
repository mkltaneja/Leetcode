
// APPROACH 1 (BFS)

class Solution {
public:
    
    #define f first
    #define s second
    int maxMoves(vector<vector<int>>& grid) 
    {
        int n = grid.size(), m = grid[0].size();
        int ans = 0;
        set<pair<int,int>> vis;
        queue<pair<int,int>> que;
        for(int i = 0; i < n; i++)
        {
            que.push({i, 0});
            vis.insert({i, 0});
        }
        
        while(!que.empty())
        {
            int sz = que.size();
            int added = 0;
            while(sz--)
            {
                int i = que.front().f;
                int j = que.front().s;
                que.pop();
                if(j == m-1) return m-1;

                if(i-1 >= 0 && grid[i-1][j+1] > grid[i][j] && !vis.count({i-1, j+1})) 
                {
                    que.push({i-1, j+1});
                    vis.insert({i-1, j+1});
                    added = 1;
                }
                if(grid[i][j+1] > grid[i][j] && !vis.count({i, j+1})) 
                {
                    que.push({i, j+1});
                    vis.insert({i, j+1});
                    added = 1;
                }
                if(i+1 < n && grid[i+1][j+1] > grid[i][j] && !vis.count({i+1, j+1})) 
                {
                    que.push({i+1, j+1});
                    vis.insert({i+1, j+1});
                    added = 1;
                }
            }
            ans += added;
        }
        
        return ans;
    }
};

// APPROACH 2 (DFS) --> [OPTIMIZED]

class Solution {
public:
    int maxMoves(vector<vector<int>>& grid) 
    {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> dp(n, vector<int> (m, 0));
        for(int j = m-2; j >= 0; j--)
        {
            for(int i = 0; i < n; i++)
            {
                if(i && grid[i-1][j+1] > grid[i][j]) dp[i][j] = max(dp[i][j], dp[i-1][j+1] + 1);
                if(grid[i][j+1] > grid[i][j]) dp[i][j] = max(dp[i][j], dp[i][j+1] + 1);
                if(i+1 < n && grid[i+1][j+1] > grid[i][j]) dp[i][j] = max(dp[i][j], dp[i+1][j+1] + 1);
            }
        }
        
        int ans = 0;
        for(int i = 0; i < n; i++)
            ans = max(ans, dp[i][0]);
        
        return ans;
    }
};
