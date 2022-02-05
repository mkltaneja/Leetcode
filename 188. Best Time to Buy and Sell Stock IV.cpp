
// dp0 -> not holding a stock
// dp1 -> holding a stock
int maxProfit(int k, vector<int> &prices)
{
    vector<int> dp0(k + 1, 0), dp1(k + 1, INT_MIN);
    for (int x : prices)
    {
        for (int i = k; i > 0; i--)
        {
            dp0[i] = max(dp0[i], dp1[i] + x);
            dp1[i] = max(dp1[i], dp0[i - 1] - x);
        }
    }
    return dp0[k];
}