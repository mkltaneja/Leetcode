
vector<int> par;
vector<int> rank;
int comps = 0;
int findpar(int u)
{
    if (par[u] == u)
        return u;
    return par[u] = findpar(par[u]);
}
void merge(int x, int y)
{
    int px = findpar(x);
    int py = findpar(y);
    if (px != py)
    {
        comps--;
        if (rank[px] > rank[py])
            par[py] = px;
        else if (rank[py] > rank[px])
            par[px] = py;
        else
        {
            par[px] = py;
            rank[py]++;
        }
    }
}

vector<int> numIslands2(int m, int n, vector<Point> &operators)
{
    vector<int> ans(operators.size());
    vector<vector<int>> gp(m, vector<int>(n, 0));
    par.resize(n * m, -1);
    rank.resize(n * m, 1);

    int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    for (int k = 0; k < operators.size(); k++)
    {
        int i = operators[k].x, j = operators[k].y;
        int idx = i * n + j;
        if (par[idx] != -1)
        {
            ans[k] = comps;
            continue;
        }

        par[idx] = idx;
        comps++;
        gp[i][j] = 1;
        for (int d = 0; d < 4; d++)
        {
            int r = i + dir[d][0], c = j + dir[d][1];
            int idx1 = r * n + c;
            if (r == -1 || c == -1 || r == m || c == n || par[idx1] == -1)
                continue;

            merge(idx, idx1);
        }
        ans[k] = comps;
    }
    return ans;
}