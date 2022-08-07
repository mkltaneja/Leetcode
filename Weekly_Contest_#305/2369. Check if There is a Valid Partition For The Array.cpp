
bool validPartition(vector<int> &nums)
{
    int n = nums.size();

    vector<int> dp(n + 1, 0);
    dp[0] = 1;

    for (int i = 1; i < n; i++)
    {
        if (nums[i] == nums[i - 1])
            dp[i + 1] |= dp[i - 1];
        if (i == 1)
            continue;

        if (nums[i] == nums[i - 1] && nums[i - 1] == nums[i - 2])
            dp[i + 1] |= dp[i - 2];

        int cons[3] = {nums[i], nums[i - 1], nums[i - 2]};
        sort(cons, cons + 3);

        if (cons[2] == cons[1] + 1 && cons[1] == cons[0] + 1)
            dp[i + 1] |= dp[i - 2];
    }

    return dp[n];
}