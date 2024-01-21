// Time Complexity = O(n^3)
// Space Complexity = O(n^2)

class Solution {
public:
    
    #define ll long long
    vector<int> countOfPairs(int n, int x, int y) 
    {
        vector<int> ans(n);
        vector<vector<ll>> dist(n+2, vector<ll>(n+2, INT_MAX));
        for(int i = 1; i <= n; i++)
        {
            dist[i][i] = 0;
            dist[i][i+1] = 1;
            dist[i+1][i] = 1;
        }
        if(x != y)
        {
            dist[x][y] = 1;
            dist[y][x] = 1;
        }
        
        for(int k = 1; k <= n; k++)
            for(int i = 1; i <= n; i++)
                for(int j = 1; j <= n; j++)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                if(dist[i][j] == 0) continue;
                ans[dist[i][j]-1]++;
            }
        }
        
        return ans;
    }
};
