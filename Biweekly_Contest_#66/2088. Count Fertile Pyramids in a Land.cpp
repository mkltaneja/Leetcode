
#define f first
#define s second

int countPyramids(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();
    vector<vector<pair<int, int>>> vp(n, vector<pair<int, int>>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 0)
            {
                vp[i][j] = {-1, -1};
                continue;
            }
            if (j && grid[i][j - 1])
                vp[i][j].f = vp[i][j - 1].f + 1;
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = m - 1; j >= 0; j--)
        {
            if (grid[i][j] == 0)
                continue;
            if (j < m - 1 && grid[i][j + 1])
                vp[i][j].s = vp[i][j + 1].s + 1;
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j])
            {
                int l = 1, r = 1;
                for (int k = i + 1; k < n; k++)
                {
                    if (vp[k][j].f >= l && vp[k][j].s >= r)
                        ans++;
                    else
                        break;
                    l++, r++;
                }
            }
        }
    }
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j])
            {
                int l = 1, r = 1;
                for (int k = i - 1; k >= 0; k--)
                {
                    if (vp[k][j].f >= l && vp[k][j].s >= r)
                        ans++;
                    else
                        break;
                    l++, r++;
                }
            }
        }
    }
    return ans;
}