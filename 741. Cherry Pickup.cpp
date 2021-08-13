
#define vi vector<int>
#define vvi vector<vi>
#define vvvi vector<vvi>

int dfs(int i1, int j1, int i2, int n, int m, vvi &arr, vvvi &dp)
{
    int j2 = i1 + j1 - i2;
    if(i1 == n || j1 == m || i2 == n || j2 == m || arr[i1][j1]==-1 || arr[i2][j2]==-1)
        return INT_MIN;
    if(dp[i1][j1][i2] != -1) return dp[i1][j1][i2];
    if(i1 == n-1 && j1 == m-1 && i2 == n-1 && j2 == m-1)
        return arr[i1][j1];
    
    
    int myAns = (i1 == i2 && j1 == j2)? arr[i1][j1] : arr[i1][j1] + arr[i2][j2];
    
    int r1 = dfs(i1 + 1, j1, i2 + 1, n, m, arr, dp);
    int d1 = dfs(i1 + 1, j1, i2, n, m, arr, dp);
    int r2 = dfs(i1, j1 + 1, i2 + 1, n, m, arr, dp);
    int d2 = dfs(i1, j1 + 1, i2, n, m, arr, dp);
    
    int mx = max({r1, d1, r2, d2});
    
    return dp[i1][j1][i2] = (mx == INT_MIN? mx : (mx + myAns));
}

int cherryPickup(vector<vector<int>>& grid) 
{
    int n = grid.size(), m = grid[0].size();
    vvvi dp(n, vvi(m, vi(n,-1)));
    int ans = dfs(0, 0, 0, n, m, grid, dp);
    return ans == INT_MIN? 0 : ans;
}