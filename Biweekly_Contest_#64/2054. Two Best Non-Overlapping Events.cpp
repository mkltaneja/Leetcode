
int maxTwoEvents(vector<vector<int>> &events)
{
    int n = events.size();
    sort(events.begin(), events.end());
    vector<int> st(n);
    vector<int> maxv(n);
    st[n - 1] = events[n - 1][0];
    maxv[n - 1] = events[n - 1][2];
    for (int i = n - 2; i >= 0; i--)
    {
        maxv[i] = max(events[i][2], maxv[i + 1]);
        st[i] = events[i][0];
    }

    int maxans = 0;
    for (int i = 0; i < n; i++)
    {
        int x = upper_bound(st.begin(), st.end(), events[i][1]) - st.begin();
        if (x == n)
            maxans = max(maxans, events[i][2]);
        else
            maxans = max(maxans, events[i][2] + maxv[x]);
    }

    return maxans;
}