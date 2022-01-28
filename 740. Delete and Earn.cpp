
// APPROACH 1 (DP -- Using space)

int findmax(vector<pair<int, int>> &cnt)
{
    int n = cnt.size();
    vector<int> dp(n + 3);
    for (int i = n - 1; i >= 0; i--)
        dp[i] = max(dp[i + 2], dp[i + 3]) + cnt[i].first * cnt[i].second;

    return max(dp[0], dp[1]);
}

int deleteAndEarn(vector<int> &nums)
{
    int n = nums.size();
    map<int, int> m;
    for (int x : nums)
        m[x]++;

    int ans = 0;
    int x = -1;
    vector<pair<int, int>> tmp;
    for (auto p : m)
    {
        if (p.first != x + 1)
        {
            ans += findmax(tmp);
            tmp.clear();
        }
        tmp.push_back({p.first, p.second});
        x = p.first;
    }
    ans += findmax(tmp);

    return ans;
}

// APPROACH 2 (DP -- Constant Space)

int deleteAndEarn(vector<int> &nums)
{
    int n = nums.size();
    map<int, int> m;
    for (int x : nums)
        m[x]++;

    int inc = 0, exc = 0;
    int prev = -1;
    for (auto p : m)
    {
        int newexc = max(inc, exc);
        int newinc = p.first * p.second + ((p.first == prev + 1) ? exc : newexc);

        inc = newinc;
        exc = newexc;
        prev = p.first;
    }

    return max(inc, exc);
}