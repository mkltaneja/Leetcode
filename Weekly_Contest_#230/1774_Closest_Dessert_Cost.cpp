
int minabs = INT_MAX, ans;

void coin_change(int idx, int m, int val, int tar, vector<int> &coins)
{
    if (abs(val - tar) <= minabs)
    {
        if ((abs(val - tar) == minabs && val <= tar) || abs(val - tar) < minabs)
        {
            ans = val;
            minabs = abs(val - tar);
        }
    }

    for (int i = idx; i < m; i++)
        coin_change(i + 1, m, val + coins[i], tar, coins);
}

int closestCost(vector<int> &baseCosts, vector<int> &toppingCosts, int target)
{
    int n = baseCosts.size(), m = toppingCosts.size();
    vector<int> a = baseCosts, b;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < 2; j++)
            b.push_back(toppingCosts[i]);
    m = b.size();

    ans = target;
    for (int i = 0; i < n; i++)
        coin_change(0, m, a[i], target, b);
    return ans;
}