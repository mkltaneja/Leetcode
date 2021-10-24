
int minimumTime(int n, vector<vector<int>> &relations, vector<int> &time)
{
    vector<vector<int>> gp(n);
    vector<int> indeg(n, 0);
    for (vector<int> v : relations)
    {
        gp[v[0] - 1].push_back(v[1] - 1);
        indeg[v[1] - 1]++;
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    for (int i = 0; i < n; i++)
        if (indeg[i] == 0)
            pq.push({time[i], i});

    int ans = 0;
    while (!pq.empty())
    {
        int sz = pq.size();
        while (sz--)
        {
            auto u = pq.top();
            pq.pop();
            ans = u.first;

            for (int v : gp[u.second])
                if (--indeg[v] == 0)
                    pq.push({u.first + time[v], v});
        }
    }

    return ans;
}