
// APPROACH 1 (Finding maximum overlap) --> O(n^2)

int maximumPopulation(vector<vector<int>> &logs)
{
    int n = logs.size();
    sort(logs.begin(), logs.end(), [](auto const &a, auto const &b) {
        return (a[0] == b[0]) ? (a[1] < b[1]) : (a[0] < b[0]);
    });
    int ans = logs[0][0], maxcnt = 0;

    for (int i = 0; i < n; i++)
    {
        int cnt = 0;
        for (int j = 0; j < n; j++)
            if (logs[i][0] >= logs[j][0] && logs[i][0] < logs[j][1])
                cnt++;
        if (cnt > maxcnt)
        {
            maxcnt = cnt;
            ans = logs[i][0];
        }
    }

    return ans;
}

// APPROACH 2 (By range addition) --> O(1)

int maximumPopulation(vector<vector<int>> &logs)
{
    int n = logs.size();
    vector<int> year(2050 - 1950 + 1, 0);
    for (auto v : logs)
    {
        year[v[0] - 1950]++;
        year[v[1] - 1950]--;
    }
    int mxi = 0;
    for (int i = 1; i < year.size(); i++)
    {
        year[i] += year[i - 1];
        if (year[i] > year[mxi])
            mxi = i;
    }

    return mxi + 1950;
}