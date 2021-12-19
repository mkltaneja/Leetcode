
long long getDescentPeriods(vector<int> &prices)
{
    long long ans = 0;
    int j = 0;
    for (int i = 0; i < prices.size();)
    {
        ans += i - j + 1;
        if (i == prices.size() - 1)
            break;
        if (prices[i] == prices[i + 1] + 1)
            i++;
        else
            j = ++i;
    }
    return ans;
}