// DAY 1 (198. House Robber)======================================================================

int rob(vector<int> &nums)
{
    int n = nums.size();
    vector<int> dp(n);
    dp[n - 1] = nums[n - 1];
    for (int i = n - 2; i >= 0; i--)
        dp[i] = max(nums[i] + ((i + 2 < n) ? dp[i + 2] : 0), dp[i + 1]);

    return dp[0];
}

// DAY 3 (152. Maximum Product Subarray)================================================================================

int maxProduct(vector<int> &nums)
{
    int ans = nums[0];
    int maxp = nums[0], minp = nums[0];
    for (int i = 1; i < nums.size(); i++)
    {
        int x = nums[i];
        if (x < 0)
            swap(minp, maxp);
        maxp = max(maxp * x, x);
        minp = min(minp * x, x);

        ans = max({ans, maxp, minp});
    }

    return ans;
}