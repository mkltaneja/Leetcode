
// dp0 -> not holding a stock
// dp1 -> holding a stock
int maxProfit(vector<int> &prices)
{
    int dp0 = 0, pdp0 = 0, dp1 = INT_MIN;
    for (int x : prices)
    {
        int tmp = dp0;
        dp0 = max(dp0, dp1 + x);
        dp1 = max(dp1, pdp0 - x);
        pdp0 = tmp;
    }
    return dp0;
}