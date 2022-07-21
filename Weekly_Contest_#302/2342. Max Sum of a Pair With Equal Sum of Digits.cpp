
int maximumSum(vector<int> &nums)
{
    vector<vector<int>> sod(100);
    for (int x : nums)
    {
        int sum = 0;
        int y = x;
        while (x)
        {
            sum += x % 10;
            x /= 10;
        }
        sod[sum].push_back(y);
    }

    int ans = -1;
    for (vector<int> &v : sod)
    {
        sort(v.begin(), v.end());
        if (v.size() < 2)
            continue;
        ans = max(ans, v[v.size() - 2] + v[v.size() - 1]);
    }

    return ans;
}