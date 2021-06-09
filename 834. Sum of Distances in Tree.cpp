
#define f first
#define s second

int countnodes(int u, int par, vector<vector<int>> &gp, vector<int> &subnodes)
{
    int count = 0;
    for (int v : gp[u])
        if (v != par)
            count += countnodes(v, u, gp, subnodes);
    return subnodes[u] = count + 1;
}

int findDist(int u, vector<vector<int>> &gp)
{

    queue<pair<pair<int, int>, int>> que;
    que.push({{u, -1}, 0});
    int dist0 = 0;

    while (!que.empty())
    {
        auto p = que.front();
        que.pop();

        dist0 += p.s;

        for (int v : gp[p.f.f])
            if (v != p.f.s)
                que.push({{v, p.f.f}, p.s + 1});
    }
    return dist0;
}

void findDistAll(int dist0, int n, vector<vector<int>> &gp, vector<int> &subnodes, vector<int> &ans)
{
    queue<pair<pair<int, int>, int>> que;
    que.push({{0, -1}, dist0}); // {{node, parent}, sum of dist}

    while (!que.empty())
    {
        auto p = que.front();
        que.pop();

        ans[p.f.f] = p.s;
        for (int v : gp[p.f.f])
        {
            if (v == p.f.s)
                continue;
            int distv = p.s - subnodes[v] + (n - subnodes[v]);
            que.push({{v, p.f.f}, distv});
        }
    }
}

vector<int> sumOfDistancesInTree(int N, vector<vector<int>> &edges)
{
    vector<vector<int>> gp(N);

    for (int i = 0; i < edges.size(); i++)
    {
        gp[edges[i][0]].push_back(edges[i][1]);
        gp[edges[i][1]].push_back(edges[i][0]);
    }

    vector<int> subnodes(N);
    countnodes(0, -1, gp, subnodes);

    int dist0 = findDist(0, gp);

    vector<int> ans(N);
    findDistAll(dist0, N, gp, subnodes, ans);

    return ans;
}