
#define f first
#define s second

int numBusesToDestination(vector<vector<int>> &routes, int source, int target)
{
    int n = routes.size();
    unordered_map<int, vector<int>> stop_route;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < routes[i].size(); j++)
            stop_route[routes[i][j]].push_back(i);

    unordered_map<int, bool> bus_vis;
    vector<bool> route_vis(n, false);
    bus_vis[source] = true;

    queue<pair<int, int>> que;
    que.push({source, 0});

    while (!que.empty())
    {
        auto p = que.front();
        que.pop();

        if (p.f == target)
            return p.s;

        for (auto route : stop_route[p.f])
        {
            if (route_vis[route])
                continue;
            route_vis[route] = true;
            for (int bus : routes[route])
            {
                if (bus_vis[bus])
                    continue;

                if (bus == target)
                    return p.s + 1;

                bus_vis[bus] = true;
                que.push({bus, p.s + 1});
            }
        }
    }
    return -1;
}