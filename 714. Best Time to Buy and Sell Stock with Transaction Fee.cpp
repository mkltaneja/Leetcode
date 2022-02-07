
int maxProfit(vector<int> &prices, int fee)
{
    int dp0 = 0, dp1 = -2e5;
    for (int x : prices)
    {
        int pdp0 = dp0;
        dp0 = max(dp0, dp1 + x - fee);
        dp1 = max(dp1, pdp0 - x);
    }
    return dp0;
}