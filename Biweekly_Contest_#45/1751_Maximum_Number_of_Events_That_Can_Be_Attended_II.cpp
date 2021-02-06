
int maxValue(vector<vector<int>> &events, int k)
{
    int n = events.size();
    sort(events.begin(), events.end());
    vector<int> starts(n);
    for (int i = 0; i < n; i++)
        starts[i] = events[i][0];

    vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
    for (int i = n - 1; i >= 0; i--)
    {
        auto itr = upper_bound(starts.begin() + i, starts.end(), events[i][1]);
        int idx = itr - starts.begin();

        for (int j = 1; j <= k; j++)
            dp[i][j] = max(dp[i + 1][j], dp[idx][j - 1] + events[i][2]);
    }
    return dp[0][k];
}