
vector<vector<int>> getSkyline(vector<vector<int>> &buildings)
{
    vector<vector<int>> pts;
    for (auto v : buildings)
    {
        pts.push_back({v[0], -v[2]});
        pts.push_back({v[1], v[2]});
    }
    sort(pts.begin(), pts.end(), [](auto const &a, auto const &b)
         { return (a[0] == b[0]) ? (a[1] < b[1]) : (a[0] < b[0]); });

    map<int, int, greater<int>> pq;
    int prevht = 0;
    vector<vector<int>> ans;
    for (auto v : pts)
    {
        if (v[1] < 0)
            pq[-v[1]]++;
        else if (--pq[v[1]] == 0)
            pq.erase(v[1]);

        int top = (*pq.begin()).first;
        if (prevht == top)
            continue;
        ans.push_back({v[0], top});
        prevht = top;
    }
    return ans;
}