// DAY 1 (312. Burst Balloons)====================================================================

int maxCoins(vector<int> &nums)
{
    vector<vector<int>> dp(nums.size() + 2, vector<int>(nums.size() + 2, 0));
    // (nums.size() + 2) is for handling the -1 and nums.size(),
    // so the convention will be l+1, r+1 everywhere
    for (int len = 2; len <= nums.size() + 1; len++)
    {
        for (int l = -1, r = l + len; r <= nums.size(); l++, r++)
        {
            int currans = 0;
            for (int i = l + 1; i < r; i++)
            {
                int lans = l == -1 ? 1 : nums[l];
                int rans = r == nums.size() ? 1 : nums[r];
                int lmax = l == -1 ? 1 : dp[l][i];
                int rmax = r == nums.size() ? 1 : dp[i][r];
                currans = max(currans, dp[l + 1][i + 1] + lans * nums[i] * rans + dp[i + 1][r + 1]);
            }
            dp[l + 1][r + 1] = currans;
        }
    }

    return dp[0][nums.size() + 1];
}

// DAY 2 (1010. Pairs of Songs With Total Durations Divisible by 60)=====================================================================

int numPairsDivisibleBy60(vector<int> &time)
{
    int n = time.size();
    unordered_map<int, int> m;
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        int mod = time[i] % 60;
        ans += m[(60 - mod) % 60];
        m[mod]++;
    }
    return ans;
}

// DAY 3 (997. Find the Town Judge)================================================================================

int findJudge(int n, vector<vector<int>> &trust)
{
    vector<int> tcnt(n, 0);
    for (vector<int> v : trust)
    {
        tcnt[v[1] - 1]++;
        tcnt[v[0] - 1]--;
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (tcnt[i] == n - 1)
        {
            if (ans)
                return -1;
            ans = i + 1;
        }
    }

    return ans ? ans : -1;
}