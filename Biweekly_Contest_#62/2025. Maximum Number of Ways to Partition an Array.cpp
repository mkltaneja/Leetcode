
int waysToPartition(vector<int> &nums, int k)
{
    int n = nums.size();
    vector<long> ssum(n), psum(n);

    for (int i = n - 1; i >= 0; i--)
        ssum[i] = (i != n - 1) ? (ssum[i + 1] + nums[i]) : nums[i];
    for (int i = 0; i < n; i++)
        psum[i] = i ? (psum[i - 1] + nums[i]) : nums[i];

    vector<vector<int>> nc;
    unordered_map<long, int> p;
    unordered_map<long, int> s;
    for (int i = 1; i < n; i++)
        s[psum[i - 1] - ssum[i]]++;

    int ans = s[0];
    for (int i = 0; i < n; i++)
    {
        int x = k - nums[i];
        ans = max(ans, p[x] + s[-x]);
        if (i != n - 1)
        {
            p[psum[i] - ssum[i + 1]]++;
            s[psum[i] - ssum[i + 1]]--;
        }
    }

    return ans;
}