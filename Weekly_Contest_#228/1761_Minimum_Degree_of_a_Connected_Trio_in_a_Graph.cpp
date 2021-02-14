
// METHOD 1 (Naive) >O(n^3)
// TLE

int indeg(int i, vector<vector<int>> &gp)
{
    int in = 0;
    for (int v : gp[i])
        in++;
    return in;
}

int trio(int i, int n, vector<vector<int>> &gp, vector<bool> &istrio)
{
    vector<int> vis(n, -1);
    vis[i] = 0;
    vector<int> e;
    int in1 = 0;
    for (int v : gp[i])
    {
        e.push_back(v);
        vis[v] = 1;
        in1++;
    }
    int ans = INT_MAX;
    for (int x : e)
    {
        for (int v : gp[x])
        {
            if (vis[v] == 1)
            {
                istrio[i] = true;
                int in2 = indeg(x, gp);
                int in3 = indeg(v, gp);
                ans = min(ans, in1 + in2 + in3 - 6);
                // return in1+in2+in3-6;
            }
        }
    }
    return ans;
}

int minTrioDegree(int n, vector<vector<int>> &edges)
{
    vector<vector<int>> gp(n);
    for (auto v : edges)
    {
        gp[v[0] - 1].push_back(v[1] - 1);
        gp[v[1] - 1].push_back(v[0] - 1);
    }

    int mindeg = INT_MAX;
    vector<bool> istrio(n, false);
    bool hastrio = false;
    for (int i = 0; i < n; i++)
    {
        // if(!istrio[i])
        // {
        int deg = trio(i, n, gp, istrio);
        // cout<<i<<" --> "<<deg<<",   ";
        mindeg = min(mindeg, deg);
        if (istrio[i])
            hastrio = true;
        // }
    }
    cout << endl;
    return hastrio ? mindeg : -1;
}

// APPROACH 2 (By making the list of connected edges and counting the degree of every vertex) --> O(n^3)

int minTrioDegree(int n, vector<vector<int>> &edges)
{
    vector<vector<bool>> e(n + 1, vector<bool>(n + 1, 0));
    vector<int> d(n + 1, 0);
    for (vector<int> v : edges)
    {
        e[v[0]][v[1]] = e[v[1]][v[0]] = 1;
        d[v[0]]++;
        d[v[1]]++;
    }

    int ans = INT_MAX;
    for (int i = 1; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (e[i][j])
                for (int k = j + 1; k <= n; k++)
                    if (e[j][k] && e[i][k])
                        ans = min(ans, d[i] + d[j] + d[k] - 6);
    return (ans == INT_MAX) ? -1 : ans;
}