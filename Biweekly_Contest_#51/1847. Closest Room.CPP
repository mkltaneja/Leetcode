
vector<int> closestRoom(vector<vector<int>> &rooms, vector<vector<int>> &queries)
{
    sort(rooms.begin(), rooms.end(), [](const auto &a, const auto &b) {
        return a[1] > b[1];
    });

    int n = queries.size();
    for (int i = 0; i < n; i++)
        queries[i].push_back(i);
    sort(queries.begin(), queries.end(), [](const auto &a, const auto &b) {
        return a[1] > b[1];
    });

    vector<int> ans(n, -1);
    set<int> s;
    for (int i = 0, j = 0; i < n; i++)
    {
        int k = queries[i][2];
        for (; j < rooms.size() && rooms[j][1] >= queries[i][1]; j++)
            s.insert(rooms[j][0]);
        auto itr = s.lower_bound(queries[i][0]);

        if (itr != s.end())
            ans[k] = *itr;
        if (itr != s.begin())
        {
            itr--;
            if ((ans[k] == -1) || ((queries[i][0] - *itr) <= (ans[k] - queries[i][0])))
                ans[k] = *itr;
        }
    }
    return ans;
}