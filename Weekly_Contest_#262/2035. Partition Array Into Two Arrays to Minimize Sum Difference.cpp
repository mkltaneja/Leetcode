
int countones(int x)
{
    int cnt = 0;
    while (x)
    {
        x -= (x & -x);
        cnt++;
    }
    return cnt;
}

int minimumDifference(vector<int> &nums)
{
    int n = nums.size() / 2;
    int ans = INT_MAX;
    vector<vector<int>> a(n + 1), b(n + 1);
    for (int x = 0; x < (1 << n); x++)
    {
        int sum = 0;
        int ones = countones(x);
        for (int i = 0; i < n; i++)
        {
            if (x & (1 << i))
                sum += nums[i];
            else
                sum -= nums[i];
        }
        a[ones].push_back(sum);
    }
    for (int x = 0; x < (1 << n); x++)
    {
        int sum = 0;
        int ones = countones(x);
        for (int i = 0; i < n; i++)
        {
            if (x & (1 << i))
                sum += nums[n + i];
            else
                sum -= nums[n + i];
        }
        b[ones].push_back(sum);
    }

    for (int i = 0; i <= n; i++)
    {
        sort(a[i].begin(), a[i].end());
        sort(b[i].begin(), b[i].end());
    }

    for (int i = 0; i <= n; i++)
    {
        for (int suma : a[i])
        {
            auto lb = lower_bound(b[i].begin(), b[i].end(), suma);
            if (lb != b[i].end())
                ans = min(ans, *lb - suma);
            if (lb != b[i].begin())
                ans = min(ans, suma - *(--lb));
        }
    }
    return ans;
}