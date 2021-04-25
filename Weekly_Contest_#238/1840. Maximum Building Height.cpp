
int maxBuilding(int n, vector<vector<int>> &restrictions)
{
    int m = restrictions.size();
    if (m == 0)
        return n - 1;

    sort(restrictions.begin(), restrictions.end());

    vector<int> l(m);
    l[0] = min(restrictions[0][0] - 1, restrictions[0][1]);
    for (int i = 1; i < m; i++)
        l[i] = min(l[i - 1] + (restrictions[i][0] - restrictions[i - 1][0]), restrictions[i][1]);

    vector<int> r(m);
    r[m - 1] = min(restrictions[m - 1][0] - 1, restrictions[m - 1][1]);
    for (int i = m - 2; i >= 0; i--)
        r[i] = min(r[i + 1] + (restrictions[i + 1][0] - restrictions[i][0]), restrictions[i][1]);

    int ans = 0;
    for (int i = 0; i < m - 1; i++)
    {
        int lh = min(l[i], r[i]);
        int rh = min(l[i + 1], r[i + 1]);
        int maxh = max(lh, rh);
        int hdiff = abs(rh - lh);
        int dist = restrictions[i + 1][0] - restrictions[i][0];
        int midh = (dist - hdiff) / 2;
        ans = max(ans, maxh + midh);
        // ans = max(ans, (lh+rh+dist)/2);
    }
    ans = max(ans, min(l[m - 1], r[m - 1]) + (n - restrictions[m - 1][0]));

    return ans;
}