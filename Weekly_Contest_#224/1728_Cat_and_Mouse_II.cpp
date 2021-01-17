
int fp, cj, mj, n, m;
vector<vector<int>> dir = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
vector<string> g;
// vector<vector<vector<int> > > dp(1010, vector<vector<int>>(20, vector<int>(20, -1)));
int dp[1001][65][65];
int dfs(int cnt, int cp, int mp)
{
    if (cnt > 130)
        return 0;
    if (mp == fp)
        return 1;
    if (cp == fp)
        return 0;
    if (cp == mp)
        return 0;
    if (dp[cnt][cp][mp] >= 0)
        return dp[cnt][cp][mp];
    if (dp[cnt][cp][mp] == -2)
        return 0;
    // cout<<cnt<<endl;
    dp[cnt][cp][mp] = -2;
    if ((cnt & 1) == 0)
    {
        int x = mp / m, y = mp % m;
        for (int d = 0; d < 4; d++)
        {
            for (int j = 0; j <= mj; j++)
            {
                int xj = x + dir[d][0] * j, yj = y + dir[d][1] * j;
                if (xj < 0 || yj < 0 || xj >= n || yj >= m || g[xj][yj] == '#')
                    break;
                int np = xj * m + yj;
                if (dfs(cnt + 1, cp, np) == 1)
                    return dp[cnt][cp][mp] = 1;
            }
        }
        return dp[cnt][cp][mp] = 0;
    }
    else
    {
        int x = cp / m, y = cp % m;
        for (int d = 0; d < 4; d++)
        {
            for (int j = 0; j <= cj; j++)
            {
                int xj = x + dir[d][0] * j, yj = y + dir[d][1] * j;
                if (xj < 0 || yj < 0 || xj >= n || yj >= m || g[xj][yj] == '#')
                    break;
                int np = xj * m + yj;
                if (dfs(cnt + 1, np, mp) == 0)
                    return dp[cnt][cp][mp] = 0;
            }
        }
        return dp[cnt][cp][mp] = 1;
    }
}

bool canMouseWin(vector<string> &grid, int catJump, int mouseJump)
{
    memset(dp, -1, sizeof(dp));
    g = grid;
    int cp, mp;
    n = grid.size(), m = grid[0].size(), cj = catJump, mj = mouseJump;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (g[i][j] == 'C')
                cp = i * m + j;
            else if (g[i][j] == 'M')
                mp = i * m + j;
            else if (g[i][j] == 'F')
                fp = i * m + j;
        }
    }
    return dfs(0, cp, mp);
}