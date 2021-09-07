
#define f first
#define s second

int lowerBound(int st, int x, vector<pair<int, pair<int, int>>> &arr)
{
    int end = arr.size();
    while (st < end)
    {
        int mid = st + (end - st) / 2;
        if (arr[mid].f < x)
            st = mid + 1;
        else
            end = mid;
    }
    return st;
}

int jobScheduling(vector<int> &startTime, vector<int> &endTime, vector<int> &profit)
{
    int n = profit.size();
    vector<pair<int, pair<int, int>>> arr(n);
    for (int i = 0; i < n; i++)
        arr[i] = {startTime[i], {endTime[i], profit[i]}};
    sort(arr.begin(), arr.end());

    vector<int> dp(n);
    int maxprofit = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        int x = lowerBound(i + 1, arr[i].s.f, arr);
        int xans = (x == n) ? 0 : dp[x];

        dp[i] = max(maxprofit, xans + arr[i].s.s);
        maxprofit = max(maxprofit, dp[i]);
    }
    return maxprofit;
}