// Method 1 (recursion)
// TLE
int mincoins = INT_MAX;
void min_combi(int idx, vector<int> &coins, int amount, int calls)
{
    if (amount == 0)
    {
        mincoins = min(mincoins, calls);
        return;
    }
    for (int i = idx; i < coins.size(); i++)
        if (amount - coins[i] >= 0)
            min_combi(i, coins, amount - coins[i], calls + 1);
}

int coinChange(vector<int> &coins, int amount)
{
    min_combi(0, coins, amount, 0);
    return (mincoins == INT_MAX) ? -1 : mincoins;
}

// Method 2 (Tabulation)
// AC
int coinChange(vector<int> &coins, int amount)
{
    vector<int> dp(amount + 1, 1e8);

    dp[0] = 0;
    for (int coin : coins)
        for (int tar = 0; tar <= amount; tar++)
            if (tar - coin >= 0)
                dp[tar] = min(dp[tar], dp[tar - coin] + 1);
    return (dp[amount] == 1e8) ? -1 : dp[amount];
}