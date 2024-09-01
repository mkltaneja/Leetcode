
// Time Complexity = O(n*m * 2^n)
// Time Complexity = O(2^n + n*m)

class Solution {
public:
    int maxScore(vector<vector<int>>& grid)
    {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> occ;
        vector<int> dp((1 << n), INT_MIN);
        dp[0] = 0;
        
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                occ.push_back({grid[i][j], i});
        sort(occ.begin(), occ.end());
        
        for(int i = 0, j = 0; i < n*m; i = j)
        {
            vector<int> ndp = dp;
            while(j < n*m && occ[j][0] == occ[i][0])
                j++;
            
            for(int mask = 0; mask < (1 << n); mask++)
            {
                for(int k = i; k < j; k++)
                {
                    int val = occ[k][0];
                    int ii = occ[k][1];
                    if(mask & (1 << ii))
                        continue;
                    
                    ndp[mask | (1 << ii)] = max(ndp[mask | (1 << ii)], dp[mask] + val);
                }
            }
            
            dp = ndp;
        }
        
        return *max_element(dp.begin(), dp.end());
    }
};
