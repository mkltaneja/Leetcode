
int minimumCost(vector<int> &cost)
{
    sort(cost.rbegin(), cost.rend());
    int ans = 0;
    for (int i = 0; i < cost.size(); i++)
        ans += (i + 1) % 3 ? cost[i] : 0;
    return ans;
}