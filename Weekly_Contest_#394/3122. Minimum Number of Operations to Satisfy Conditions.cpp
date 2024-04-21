
// Time Complexity = O(n*m + m*10 + m*10*10)
// Space Complexity = O(m*10)

class Solution {
public:
    
    int minOps(int i, int p, int n, int m, vector<vector<int>> &cnt, vector<vector<int>> &cache)
    {
        if(i == m)
            return 0;
        if(cache[i][p] != -1)
            return cache[i][p];
        int ans = INT_MAX;
        for(int j = 0; j < 10; j++)
            if(j != p)
                ans = min(ans, minOps(i+1, j, n, m, cnt, cache) + cnt[i][j]);
        return cache[i][p] = ans;
    }
    
    int minimumOperations(vector<vector<int>>& grid) 
    {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> cache(m, vector<int>(12, -1));
        vector<vector<int>> cnt(m, vector<int>(10, 0));

        for(int j = 0; j < m; j++)
            for(int i = 0; i < n; i++)
                cnt[j][grid[i][j]]++;
        for(int i = 0; i < m; i++)
            for(int j = 0; j < 10; j++)
                cnt[i][j] = n - cnt[i][j];
        
        return minOps(0, 10, n, m, cnt, cache);
    }
};
