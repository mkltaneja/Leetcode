
vector<int> par;
vector<int> rank;
int findPar(int u)
{
    if (par[u] == u)
        return u;
    return findPar(par[u]);
}

bool merge(int x, int y)
{
    int px = findPar(x);
    int py = findPar(y);
    if (px == py)
        return true;

    if (rank[px] > rank[py])
        par[py] = px;
    else if (rank[py] > rank[px])
        par[px] = py;
    else
    {
        par[py] = px;
        rank[px]++;
    }
    return false;
}

int regionsBySlashes(vector<string> &grid)
{
    int n = grid.size() + 1; // n is number of dots(points) in a row
    par.resize(n * n);
    rank.resize(n * n, 1);
    for (int i = 0; i < n * n; i++)
        par[i] = i;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i == 0 || j == 0 || i == n - 1 || j == n - 1)
                merge(0, i * n + j);

    int ans = 1;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (grid[i][j] == '/')
            {
                int idx1 = i * n + (j + 1);
                int idx2 = (i + 1) * n + j;
                if (merge(idx1, idx2))
                    ans++;
            }
            else if (grid[i][j] == '\\')
            {
                int idx1 = i * n + j;
                int idx2 = (i + 1) * n + (j + 1);
                if (merge(idx1, idx2))
                    ans++;
            }
        }
    }
    return ans;
}