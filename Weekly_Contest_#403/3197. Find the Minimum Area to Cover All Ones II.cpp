
// Time Complexity = O(n^3 * m^3)
// Space Complexity = O(n^2 * m^2)

class Solution {
public:
    
    int dp[31][31][31][31];
    vector<vector<int>> ones;
    
    int getTotalOnes(int l, int r, int u, int d)
    {
        if(l > r || u > d)
            return 0;
        return ones[d][r] - (l? ones[d][l-1] : 0) - (u? ones[u-1][r] : 0) + (u && l? ones[u-1][l-1] : 0);
    }
    
    int getMinArea(int l, int r, int u, int d)
    {
        int totalOnes = getTotalOnes(l, r, u, d);
        if(totalOnes == 0)
            return 0;
        if(dp[l][r][u][d] != -1)
            return dp[l][r][u][d];
        
        int minArea = (r-l+1) * (d-u+1);
        if(getTotalOnes(l+1, r, u, d) == totalOnes)
            minArea = min(minArea, getMinArea(l+1, r, u, d));
        if(getTotalOnes(l, r-1, u, d) == totalOnes)
            minArea = min(minArea, getMinArea(l, r-1, u, d));
        if(getTotalOnes(l, r, u+1, d) == totalOnes)
            minArea = min(minArea, getMinArea(l, r, u+1, d));
        if(getTotalOnes(l, r, u, d-1) == totalOnes)
            minArea = min(minArea, getMinArea(l, r, u, d-1));
        
        return dp[l][r][u][d] = minArea;
    }
    
    int minimumSum(vector<vector<int>>& grid)
    {
        int n = grid.size(), m = grid[0].size();
        memset(dp, -1, sizeof(dp));
        ones.assign(n, vector<int>(m, 0));
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                ones[i][j] = grid[i][j] + ((i? ones[i-1][j] : 0) + (j? ones[i][j-1] : 0) - ((i && j)? ones[i-1][j-1] : 0));
        
        int minArea = INT_MAX;
        for(int i = 0; i < n-2; i++)
            for(int j = i+1; j < n-1; j++)
                minArea = min(minArea, getMinArea(0, m-1, 0, i) + getMinArea(0, m-1, i+1, j) + getMinArea(0, m-1, j+1, n-1));
        for(int i = 0; i < m-2; i++)
            for(int j = i+1; j < m-1; j++)
                minArea = min(minArea, getMinArea(0, i, 0, n-1) + getMinArea(i+1, j, 0, n-1) + getMinArea(j+1, m-1, 0, n-1));
        
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                minArea = min(minArea, getMinArea(0, m-1, 0, i) + getMinArea(0, j, i+1, n-1) + getMinArea(j+1, m-1, i+1, n-1));
                minArea = min(minArea, getMinArea(0, m-1, i+1, n-1) + getMinArea(0, j, 0, i) + getMinArea(j+1, m-1, 0, i));
                minArea = min(minArea, getMinArea(0, j, 0, n-1) + getMinArea(j+1, m-1, 0, i) + getMinArea(j+1, m-1, i+1, n-1));
                minArea = min(minArea, getMinArea(j+1, m-1, 0, n-1) + getMinArea(0, j, 0, i) + getMinArea(0, j, i+1, n-1));
            }
        }
        return minArea;
    }
};
