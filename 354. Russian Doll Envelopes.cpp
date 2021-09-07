
// APPROACH 1 (Linear Search) --> O(n^2)

int maxEnvelopes(vector<vector<int>> &envelopes)
{
    int n = envelopes.size();
    sort(envelopes.begin(), envelopes.end(), [](const auto &a, const auto &b)
         { return (a[0] == b[0]) ? (a[1] < b[1]) : (a[0] < b[0]); });
    int maxlen = 1;
    vector<int> dp(n, 1);
    for (int i = 1; i < n; i++)
    {
        int len = 1;
        for (int j = 0; j < i; j++)
            if (envelopes[j][0] < envelopes[i][0] && envelopes[j][1] < envelopes[i][1] && dp[j] + 1 > dp[i])
                dp[i] = dp[j] + 1;
        maxlen = max(maxlen, dp[i]);
    }
    return maxlen;
}

// APPROACH 2 (Using Binary Search) --> O(n*logn)

int maxEnvelopes(vector<vector<int>> &envelopes)
{
    int n = envelopes.size();
    sort(envelopes.begin(), envelopes.end(), [](const auto &a, const auto &b)
         { return a[0] == b[0] ? a[1] > b[1] : a[0] < b[0]; });

    vector<int> dp(n);
    int maxlen = 0;
    for (vector<int> v : envelopes)
    {
        int l = 0, h = maxlen;
        while (l < h)
        {
            int m = l + (h - l) / 2;
            if (dp[m] < v[1])
                l = m + 1;
            else
                h = m;
        }
        dp[l] = v[1];
        if (l == maxlen)
            maxlen++;
    }
    return maxlen;
}