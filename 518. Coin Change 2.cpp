
int change(int amount, vector<int> &coins)
{
    sort(coins.begin(), coins.end());
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;
    for (int x : coins)
    {
        for (int tar = 0; tar <= amount; tar++)
        {
            if (x > tar)
                continue;
            dp[tar] += dp[tar - x];
        }
    }
    return dp[amount];
}