
int longestIdealString(string s, int k)
{
    vector<int> dp(26);
    int ans = 0;

    for (char c : s)
    {
        int mx = 0;
        for (int i = 0; i <= k && (c - 'a') - i >= 0; i++)
            mx = max(mx, dp[(c - 'a') - i]);
        for (int i = 1; i <= k && (c - 'a') + i < 26; i++)
            mx = max(mx, dp[(c - 'a') + i]);
        ans = max(ans, mx + 1);

        dp[c - 'a'] = mx + 1;
    }
    return ans;
}